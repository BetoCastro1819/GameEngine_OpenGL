#include "Material.h"
#include <stdio.h>
#include <GL\glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Material::BMPData Material::dataStruct;

Material::Material() {
}

Material::~Material() {
}

unsigned int Material::LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {
	// Create Shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// read Shader code from text file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read Fragment Shader code from file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}
	

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}


	// Link program
	printf("Linking program\n");
	m_ProgramID = glCreateProgram();
	glAttachShader(m_ProgramID, VertexShaderID);
	glAttachShader(m_ProgramID, FragmentShaderID);
	glLinkProgram(m_ProgramID);

	// Check programa
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(m_ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(m_ProgramID, VertexShaderID);
	glDetachShader(m_ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return m_ProgramID;
}

unsigned int Material::Load_BMP(const char* imagePath) {
	FILE * file = NULL;
	if (fopen_s(&file, imagePath, "rb") != 0) { printf("Image could not be opened\n"); return 0; }

	if (fread_s(dataStruct.header, sizeof(dataStruct.header), 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}
	if (dataStruct.header[0] != 'B' || dataStruct.header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}
	dataStruct.dataPos = *(int*)&(dataStruct.header[0x0A]);
	dataStruct.imageSize = *(int*)&(dataStruct.header[0x22]);
	dataStruct.width = *(int*)&(dataStruct.header[0x12]);
	dataStruct.height = *(int*)&(dataStruct.header[0x16]);

	// Algunos archivos BMP tienen un mal formato, así que adivinamos la información faltante
	if (dataStruct.imageSize == 0)    dataStruct.imageSize = dataStruct.width * dataStruct.height * 3; // 3 : un byte por cada componente Rojo (Red), Verde (Green) y Azul(Blue)
	if (dataStruct.dataPos == 0)      dataStruct.dataPos = 54; // El encabezado del BMP está hecho de ésta manera

	if (dataStruct.data)
		delete dataStruct.data;
	dataStruct.data = new unsigned char[dataStruct.imageSize];

	fseek(file, dataStruct.dataPos, 0);

	// Leemos la información del archivo y la ponemos en el buffer
	fread(dataStruct.data, 1, dataStruct.imageSize, file);

	//Todo está en memoria ahora, así que podemos cerrar el archivo
	fclose(file);

	unsigned int textureID;
	glGenTextures(1, &textureID);

	// Se "Ata" la nueva textura : Todas las futuras funciones de texturas van a modificar esta textura
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Se le pasa la imagen a OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dataStruct.width, dataStruct.height, 0, GL_BGR, GL_UNSIGNED_BYTE, dataStruct.data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}

void Material::SetMatrixProperty(const char* name, const glm::mat4& mat) {
	m_MatrixID = glGetUniformLocation(m_ProgramID, name);
	glUniformMatrix4fv(m_MatrixID, 1, GL_FALSE, &mat[0][0]);
}

void Material::SetTextureProperty(const char* name, unsigned int textureID) {
	m_TextureID = glGetUniformLocation(m_ProgramID, name);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Set our "myTextureSampler" to use Texture Unit 0
	glUniform1i(m_TextureID, 0);
}





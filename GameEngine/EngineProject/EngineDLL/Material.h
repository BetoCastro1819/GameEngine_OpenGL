#pragma once
#include "Exports.h"
#include "glm/glm.hpp"

class ENGINEDLL_API Material {
private:
	static bool m_compiled;

	unsigned int m_ProgramID;
	unsigned int m_MatrixID;
	unsigned int m_TextureID;
	
	unsigned int CompileShaders(const char * vertex_file_path, const char * fragment_file_path);

public:
	struct BMPData {
		unsigned char header[54]; // Each BMP file begins by a 54-bytes header
		unsigned int dataPos;     // Position in the file where the actual data begins
		unsigned int width, height;
		unsigned int imageSize;   // = width*height*3
								  // Información RGB
		unsigned char * data;
	};
	
	static BMPData dataStruct;

	Material();
	~Material();
	unsigned int LoadShaders(const char * vertex_file_path, const char * fragment_file_path);	
	unsigned int Load_BMP(const char* imagePath);
	void SetMatrixProperty(const char* name, const glm::mat4& mat);
	void SetTextureProperty(const char* name, unsigned int textureID);
};


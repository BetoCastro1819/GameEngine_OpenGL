#include "Renderer.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

Renderer::Renderer(Window* window) {	
	_window = window;

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	//_projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	// Orthographic camera in world coordinates
	_projection = glm::ortho(
		0.0f,								// LEFT
		(float)_window->GetWidth(),			// RIGHT
		0.0f,								// BOTTOM
		(float)_window->GetHeight(),		// TOP
		0.0f,								// zNear
		100.0f								// zFar
	);

	// Camera matrix
	_view = glm::lookAt(
		glm::vec3(0, 0, 4), // Camera is at (0,0,-4), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	LoadIdentityMatrix();
}

Renderer::~Renderer() {
}

bool Renderer::Start() {
	cout << "Renderer::Start()" << endl;
	if (_window) {
		glfwMakeContextCurrent((GLFWwindow*)_window->GetWindowPtr());		
		if (glewInit() == GLEW_OK) {
			glGenVertexArrays(1, (&_vrtxArrID));
			glBindVertexArray(_vrtxArrID);
			return true;
		}
	}
	return false;
}

bool Renderer::Stop() {
	cout << "Renderer::Stop()" << endl;
	return true;
}

void Renderer::SetClearColor(const float& r, const float& g, const float& b, const float& a) {
	glClearColor(r, g, b, a);
}

void Renderer::ClearBuffer() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::RecalculateFragmentDepth() {
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
}

void Renderer::SwapBuffers()  {
	glfwSwapBuffers((GLFWwindow*)_window->GetWindowPtr());
}

unsigned int Renderer::GenBuffer(float* buffer, int size) {
	unsigned int vrtxBuffer;

	glGenBuffers(1, &vrtxBuffer);									// Generates buffer using vrtxBuffer
	glBindBuffer(GL_ARRAY_BUFFER, vrtxBuffer);						// Bind openGL with vrtxBuffer
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);	// OpenGL recieves buffer data
	
	return vrtxBuffer;
}

void Renderer::BindBuffer(unsigned int bufferID, int vtxCount, int attribID, int size, int drawMode) {
	glEnableVertexAttribArray(attribID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	// Structure of shader data
	glVertexAttribPointer(
		attribID,           // Atributte ID. 0 = vertexAttribute | 1 = colorAttribute
		size,               // SIZE -> 3 for triangles - 2 for UVs
		GL_FLOAT,           // TYPE
		GL_FALSE,           // NORMALIZED
		0,                  // STRIDE = "pass"
		(void*)0            // ARRAY BUFFER OFFSET
	);

	// DRAW
	// Starts from index 0, up to "vrtxCount" (vrtxCount = 3 -> triangle)
	switch (drawMode)
	{
	case 0:
		glDrawArrays(GL_TRIANGLES, 0, vtxCount);
		break;
	case 1:
		glDrawArrays(GL_TRIANGLE_STRIP, 0, vtxCount);
		break;
	case 2:
		glDrawArrays(GL_TRIANGLE_FAN, 0, vtxCount);
		break;
	}
	glDisableVertexAttribArray(0);
}

void Renderer::BindMaterial(unsigned int programID) {
	glUseProgram(programID);
}

void Renderer::LoadIdentityMatrix() {
	_model = glm::mat4(1.0f);
}

void Renderer::UpdateModelMatrix(glm::mat4 matrix) {
	_model = matrix;
}

void Renderer::MultiplyModelMatrix(glm::mat4 matrix) {
	//To multiply model's matrix, with parent's model matrix
}

void Renderer::UpdateMVP() {
	// Our ModelViewProjection : multiplication of our 3 matrices
	MVP = _projection * _view * _model; // Matrix multiplication reads from right to left
}

unsigned int Renderer::SetMatrixID(unsigned int programID) {
	return glGetUniformLocation(programID, "MVP");
}

void Renderer::SendTransformationToShader(unsigned int matrixID) {
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
}

unsigned int Renderer::SetTextureID(unsigned int programID) {
	return glGetUniformLocation(programID, "myTextureSample");
}

void Renderer::BindTexture(unsigned int texture) {
	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Renderer::SetTextureSampler(unsigned int textureID) {
	glUniform1i(textureID, 0);
}

void Renderer::DeleteBuffers(unsigned int buffer) {
	glDeleteBuffers(1, &buffer);
}

void Renderer::DeleteProgram(unsigned int programID) {
	glDeleteProgram(programID);
}

void Renderer::DeleteVrtxArray() {
	glDeleteVertexArrays(1, &_vrtxArrID);
}

void Renderer::DeleteTextures(unsigned int texture) {
	glDeleteTextures(1, &texture);
}


#pragma once
#include <iostream>

#include "Exports.h"
#include "Window.h"

// GLM -> math library
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace std;

class ENGINEDLL_API Renderer {
private:
	Window* m_window;
	unsigned int m_vertexArrayID;

 	glm::mat4 m_MVP;
	glm::mat4 m_projection;
	glm::mat4 m_model;
	glm::mat4 m_view;

public:
	Renderer(Window* window);
	~Renderer();

	bool Start();
	bool Stop();
	
	// Buffer
	unsigned int GenBuffer(float* buffer, int size);
	void BindBuffer(unsigned int bufferID, int vtxCount, int attribID, int size, int drawMode);
	void SetClearColor(const float& r, const float& g, const float& b, const float& a);
	void ClearBuffer();
	void SwapBuffers();
	void RecalculateFragmentDepth();
	
	// Material/Shader
	void BindMaterial(unsigned int programID);
	
	// Matrix operations
	void LoadIdentityMatrix();
	void UpdateModelMatrix(glm::mat4 matrix);
	void MultiplyModelMatrix(glm::mat4 matrix);
	void UpdateMVP();
	void SendTransformationToShader(unsigned int matrixID);
	unsigned int SetMatrixID(unsigned int programID);
	glm::mat4 GetMVP() { return m_MVP; }

	// Handle UV Texture
	unsigned int SetTextureID(unsigned int programID);
	void BindTexture(unsigned int texture);
	void SetTextureSampler(unsigned int textureID);

	// Free memory space
	void DeleteBuffers(unsigned int buffer);
	void DeleteVrtxArray();
	void DeleteProgram(unsigned int programID);
	void DeleteTextures(unsigned int texture);

};




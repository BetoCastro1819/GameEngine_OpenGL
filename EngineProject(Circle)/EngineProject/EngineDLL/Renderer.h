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
	Window* _window;
	unsigned int _vrtxArrID;

 	glm::mat4 MVP;
	glm::mat4 _projection;
	glm::mat4 _model;
	glm::mat4 _view;

public:
	Renderer(Window* window);
	~Renderer();

	bool Start();
	bool Stop();
	
	// Buffer
	unsigned int GenBuffer(float* buffer, int size);
	void BindBuffer(unsigned int bufferID, int vtxCount, int attribID);
	void SetClearColor(const float& r, const float& g, const float& b, const float& a);
	void ClearBuffer();
	void SwapBuffers();
	void DeleteBuffers(unsigned int _buffer);
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

	// DRAW CIRCLE????
	void DrawCircle(float x, float y, float z, float radius, int numberOfSides);
};


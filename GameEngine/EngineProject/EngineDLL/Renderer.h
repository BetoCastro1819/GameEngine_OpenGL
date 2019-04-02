#pragma once
#include <iostream>

#include "Exports.h"
#include "Window.h"

// GLM -> math library
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace std;

enum CameraType
{
	PERSPECTIVE,
	ORTHOGRAPHIC
};

class ENGINEDLL_API Renderer {
private:
	Window* _window;
	unsigned int _vrtxArrID;

 	glm::mat4 MVP;
	glm::mat4 _projection;
	glm::mat4 _model;
	glm::mat4 _view;

public:
	Renderer(Window* window, CameraType camType);
	~Renderer();

	bool Start();
	bool Stop();
	
	void SetPerpectiveCam(float fovAngle, float aspect, float near, float far);
	void SetOrthographicCam(float left, float right, float bottom, float top, float zNear, float zFar);
	void SetCamView(glm::vec3 camPos, glm::vec3 lookAt, glm::vec3 head);

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
	glm::mat4 GetMVP() { return MVP; }

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




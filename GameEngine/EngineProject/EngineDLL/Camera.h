#pragma once

#pragma once
#include <iostream>

#include "Exports.h"
#include "Window.h"
#include "Renderer.h"


// GLM -> math library
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class ENGINEDLL_API Camera {
private:
	Renderer* m_Renderer;
	glm::vec3 m_Pos;
	glm::vec3 m_Rot;

	glm::vec3 m_Head;
	glm::vec3 m_Side;
	glm::vec3 m_Foward;
	glm::vec3 m_FocusPoint;

	glm::mat4 m_ViewMat;
	glm::mat4 m_RotationMat;

	void CalculateUnitVectors();

public:
	Camera(Renderer* renderer);
	Camera(Renderer* renderer, glm::vec3 worldPos, glm::vec3 lookAt, glm::vec3 head);
	~Camera();

	void SetPosition(glm::vec3 worldPos);
	void SetRotation(glm::vec3 rotation);
	void SetFocusPoint(glm::vec3 focusPoint);

	glm::mat4 GetViewMatrix() { return m_ViewMat; }
	glm::vec3 GetPosition() { return m_Pos; }

	// Movement
	void Walk(float speed);
	void Strafe(float speed);

	// Rotation
	void Pitch(float angle);
	void Yaw(float angle);
	void Roll(float angle);
};


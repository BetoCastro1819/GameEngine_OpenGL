#pragma once

#pragma once
#include <iostream>

#include "Exports.h"
#include "Window.h"
#include "Renderer.h"


// GLM -> math library
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct CursorPos {
	double x;
	double y;
};

class ENGINEDLL_API Camera {
private:
	Renderer* m_Renderer;
	Window*   m_Window;

	glm::vec3 m_Pos;
	glm::vec3 m_Rot;

	glm::vec3 m_Head;
	glm::vec3 m_Right;
	glm::vec3 m_Foward;

	glm::mat4 m_ViewMat;
	glm::mat4 m_RotationMat;
	
	CursorPos m_PrevCursorPos;
	CursorPos m_CursorPos;

	float m_Speed;
	float m_RotationSpeed;

	void UpdateViewMatrix();
	void UpdateCursorPos();

public:
	Camera(Renderer* renderer, Window* window);
	~Camera();
	
	void UpdatePosition(float deltaTime);
	void UpdateRotation(float deltaTime);

	//void SetRotation(glm::vec3 rotation);
	//void SetFocusPoint(glm::vec3 focusPoint);

	void SetPosition(glm::vec3 worldPos) { m_Pos = worldPos; }
	glm::vec3 GetPosition() const { return m_Pos; }

	//void SetFocusPoint(glm::vec3 focusPoint) { m_FocusPoint = focusPoint; }

	// Movement
	void Walk(float speed);
	void Strafe(float speed);

	// Rotation
	void Pitch(float angle);
	void Yaw(float angle);
	void Roll(float angle);
};


#pragma once

#pragma once
#include <iostream>

#include "Exports.h"
#include "Window.h"
#include "Renderer.h"

// GLM -> math library
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct World {
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 foward;
};

struct CursorPos {
	double x;
	double y;
};

class ENGINEDLL_API Camera {
private:
	Renderer* m_Renderer;
	Window* m_Window;

	World m_World;

	glm::vec3 m_Pos;
	glm::vec3 m_Rot;

	glm::vec3 m_CameraUp;
	glm::vec3 m_CameraRight;
	glm::vec3 m_CameraFoward;
	glm::vec3 m_CameraTarget;

	glm::mat4 m_ViewMat;
	glm::mat4 m_RotationMat;
	
	CursorPos m_PrevCursorPos;
	CursorPos m_CursorPos;

	float m_Speed;
	float m_RotationSpeed;
	float m_Timer;

	void UpdateUnitVectors();
	
	void UpdateViewMatrix();
	void UpdateCursorPos();

	void CheckForMovementInput(float deltaTime);
	void CheckForRotationInput(float deltaTime);

public:
	Camera(Renderer* renderer, Window* window);
	~Camera();
	
	void Update(float deltaTime);

	// Rotate around origin at "radius" distance
	void RotateAround(glm::vec3 target, float distFromTarget, float speed, float deltaTime);

	void SetPosition(const glm::vec3& worldPos);
	void SetPosition(float x, float y, float z);
	glm::vec3 GetPosition() const { return m_Pos; }

	// Movement
	void Walk(float speed);
	void Strafe(float speed);

	// Rotation
	void Pitch(float angle);
	void Yaw(float angle);
	void Roll(float angle);
};


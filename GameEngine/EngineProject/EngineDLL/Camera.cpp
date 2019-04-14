#include "Camera.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

Camera::Camera(Renderer* renderer, Window* window) {

	m_Renderer = renderer;
	m_Window = window;

	// Setup world unit vectors
	m_World.right	= glm::vec3(1, 0, 0);
	m_World.up		= glm::vec3(0, 1, 0);
	m_World.foward	= glm::vec3(0, 0, 1);

	// Initial position and rotation
	m_Pos = glm::vec3(0, 0, 4);
	m_Rot = glm::vec3(0);

	// yaw value at 0, look to the right
	m_Rot.y = -90;

	// Camera will start by looking at world origin
	m_CameraTarget = glm::vec3(0, 0, 0);

	// Setup Unit vectors
	m_CameraFoward		= glm::vec3(0, 0, -1);
	m_CameraRight		= glm::normalize(glm::cross(m_World.up, m_CameraFoward));
	m_CameraUp			= glm::normalize(glm::cross(m_CameraFoward, m_CameraRight));

	// Init speeds
	m_Speed			= 5.0f;
	m_RotationSpeed = 100.0f;

	// Init timer
	m_Timer = 0.0f;

	// Setup camera view matrix
	m_ViewMat = glm::lookAt(
		m_Pos,
		m_CameraTarget,
		m_CameraUp
	);
	m_Renderer->SetCamView(m_ViewMat);


	// Store cursor's position by reference to local variable
	// Position is based on screen coordinates relative 
	// to the top-left corner of the window context
	//glfwGetCursorPos(
	//	(GLFWwindow*)window->GetWindowPtr(),	// window context
	//	&m_PrevCursorPos.x,					// Get Cursor X Pos
	//	&m_PrevCursorPos.y					// Get Cursor Y Pos
	//);
	//m_CursorPos = m_PrevCursorPos;
	//
}

Camera::~Camera() {
}

// Movement
void Camera::Walk(float speed) {
	m_Pos += m_CameraFoward * speed;
}

void Camera::Strafe(float speed) {
	m_Pos += m_CameraRight * speed;
}

void Camera::Pitch(float angle) {
	m_Rot.x += angle;
}

void Camera::Yaw(float angle) {
	m_Rot.y += angle;
}

void Camera::Roll(float angle) {
	m_Rot.z += angle;
}

void Camera::Update(float deltaTime) {
	UpdatePosition(deltaTime);
	UpdateRotation(deltaTime);

	UpdateViewMatrix();
}

void Camera::UpdatePosition(float deltaTime) {
	
	float movementSpeed = m_Speed * deltaTime;

	// Move forward
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_W) == GLFW_PRESS) {
		Walk(movementSpeed);
	}
	// Move backward
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_S) == GLFW_PRESS) {
		Walk(-movementSpeed);
	}
	// Strafe right
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_D) == GLFW_PRESS) {
		Strafe(movementSpeed);
	}
	// Strafe left
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_A) == GLFW_PRESS) {
		Strafe(-movementSpeed);
	}
}

void Camera::UpdateRotation(float deltaTime) {

	// Yaw
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		Yaw(m_RotationSpeed * deltaTime);
	}
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		Yaw(-m_RotationSpeed * deltaTime);
	}

	// Pitch
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_UP) == GLFW_PRESS) {
		Pitch(m_RotationSpeed * deltaTime);
	}
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_DOWN) == GLFW_PRESS) {
		Pitch(-m_RotationSpeed * deltaTime);
	}

	// Roll
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_E) == GLFW_PRESS) {
		Roll(m_RotationSpeed * deltaTime);
	}
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_Q) == GLFW_PRESS) {
		Roll(-m_RotationSpeed * deltaTime);
	}

	UpdateUnitVectors();

}

void Camera::RotateAround(glm::vec3 target, float distFromTarget, float speed, float deltaTime) {
	m_Timer += deltaTime * speed;

	float camX = sin(m_Timer) * distFromTarget;
	float camZ = cos(m_Timer) * distFromTarget;
	m_Pos = glm::vec3(camX, 0.0f, camZ);

	m_ViewMat = glm::lookAt(m_Pos, target, m_CameraUp);
	m_Renderer->SetCamView(m_ViewMat);
}

void Camera::UpdateUnitVectors() {
	// Foward
	glm::vec3 newFoward;
	newFoward.x = cos(glm::radians(m_Rot.x)) * cos(glm::radians(m_Rot.y));
	newFoward.y = sin(glm::radians(m_Rot.x));
	newFoward.z = cos(glm::radians(m_Rot.x)) * sin(glm::radians(m_Rot.y));
	m_CameraFoward = glm::normalize(newFoward);
	
	// Right
	m_CameraRight = glm::normalize(glm::cross(m_CameraFoward, m_World.up));
	
	// Up
	//m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFoward));
}

void Camera::UpdateCursorPos() {
	glfwGetCursorPos(
		(GLFWwindow*)m_Window->GetWindowPtr(),
		&m_CursorPos.x, 
		&m_CursorPos.y
	);
}

void Camera::UpdateViewMatrix() {
	m_ViewMat = glm::lookAt(
		m_Pos,
		m_Pos + m_CameraFoward,
		m_CameraUp
	);
	m_Renderer->SetCamView(m_ViewMat);
}
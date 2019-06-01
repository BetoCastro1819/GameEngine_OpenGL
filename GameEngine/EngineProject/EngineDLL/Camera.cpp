#include "Camera.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

Camera::Camera(Renderer* renderer, Window* window) {
	m_Renderer = renderer;
	m_Window = window;

	// Setup world unit vectors
	m_World.right = glm::vec3(1, 0, 0);
	m_World.up = glm::vec3(0, 1, 0);
	m_World.foward = glm::vec3(0, 0, 1);

	// Initial position and rotation
	m_Pos = glm::vec3(0, 0, 10);
	m_Rot = glm::vec3(0);
	m_RotationMat = glm::mat4(1.0f);
	Yaw(180);

	// Camera will start by looking at world origin
	m_CameraTarget = glm::vec3(0, 0, 0);

	// Setup Unit vectors
	m_CameraFoward = glm::normalize(m_CameraTarget - m_Pos);
	m_CameraRight = glm::normalize(glm::cross(m_World.up, m_CameraFoward));
	m_CameraUp = glm::normalize(glm::cross(m_CameraFoward, m_CameraRight));

	// Init speeds
	m_Speed	= 5.0f;
	m_RotationSpeed = 100.0f;

	// Init timer
	m_Timer = 0.0f;
	
	UpdateViewMatrix();
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
	m_Rot.x = angle;
	m_RotationMat *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rot.x), m_World.right);
	UpdateUnitVectors();
}

void Camera::Yaw(float angle) {
	m_Rot.y = angle;
	m_RotationMat *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rot.y), m_World.up);
	UpdateUnitVectors();
}

void Camera::Roll(float angle) {
	m_Rot.z = angle;
	m_RotationMat *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rot.z), m_World.foward);
	UpdateUnitVectors();
}

void Camera::Update(float deltaTime) {
	CheckForMovementInput(deltaTime);
	CheckForRotationInput(deltaTime);

	//UpdateViewMatrix();
}

void Camera::CheckForMovementInput(float deltaTime) {
	
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

void Camera::CheckForRotationInput(float deltaTime) {

	// Yaw
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		Yaw(-m_RotationSpeed * deltaTime);
	}
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		Yaw(m_RotationSpeed * deltaTime);
	}

	// Pitch
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_UP) == GLFW_PRESS) {
		Pitch(-m_RotationSpeed * deltaTime);
	}
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_DOWN) == GLFW_PRESS) {
		Pitch(m_RotationSpeed * deltaTime);
	}

	// Roll
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_E) == GLFW_PRESS) {
		Roll(m_RotationSpeed * deltaTime);
	}
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_Q) == GLFW_PRESS) {
		Roll(-m_RotationSpeed * deltaTime);
	}
}


void Camera::UpdateUnitVectors() {
	// Foward
	glm::vec4 newFoward = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	newFoward = m_RotationMat * newFoward;
	m_CameraFoward.x = newFoward.x;
	m_CameraFoward.y = newFoward.y;
	m_CameraFoward.z = newFoward.z;

	// Up
	glm::vec4 newUp = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	newUp = m_RotationMat * newUp;
	m_CameraUp.x = newUp.x;
	m_CameraUp.y = newUp.y;
	m_CameraUp.z = newUp.z;
	
	// Right
	m_CameraRight = glm::normalize(glm::cross(m_CameraFoward, m_CameraUp));
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

void Camera::RotateAround(glm::vec3 target, float distFromTarget, float speed, float deltaTime) {
	m_Timer += deltaTime * speed;

	float camX = sin(m_Timer) * distFromTarget;
	float camZ = cos(m_Timer) * distFromTarget;
	m_Pos = glm::vec3(camX, 0.0f, camZ);

	m_ViewMat = glm::lookAt(m_Pos, target, m_CameraUp);
	m_Renderer->SetCamView(m_ViewMat);
}

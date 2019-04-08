#include "Camera.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

Camera::Camera(Renderer* renderer, Window* window) {

	m_Renderer	= renderer;
	m_Window	= window;

	m_Pos		= glm::vec3(0, 0, -4);
	m_Rot		= glm::vec3(0);
	
	m_Right		= glm::vec3(1, 0, 0);
	m_Head		= glm::vec3(0, 1, 0);
	m_Foward	= glm::vec3(0, 0, 1);

	m_Speed		= 5.0f;

	// Get cursor position
	glfwGetCursorPos((GLFWwindow*)window->GetWindowPtr(), &m_InitialCursorPos.x, &m_InitialCursorPos.y);
	m_CurrentCursorPos = m_InitialCursorPos;

	UpdateViewMatrix();
}

Camera::~Camera() {
}

// Movement
void Camera::Walk(float speed) {
	m_Pos += m_Foward * speed;
	UpdateViewMatrix();
}

void Camera::Strafe(float speed) {
	m_Pos += m_Right * speed;
	UpdateViewMatrix();
}

// Rotation
void Camera::Pitch(float angle) {

	// Generate new m_Head position based on "angle" provided
	glm::vec3 newHead;
	newHead.x = m_Head.x;
	newHead.y = m_Head.y * glm::cos(angle) - m_Head.z * glm::sin(angle);
	newHead.z = m_Head.y * glm::sin(angle) + m_Head.z * glm::cos(angle);

	m_Head = glm::normalize(newHead);

	// Recalculate Foward Vector
	m_Foward = glm::normalize(glm::cross(m_Head, m_Right));
	
	UpdateViewMatrix();
}

void Camera::Yaw(float angle) {

	// Generate new m_Head position based on "angle" provided
	glm::vec3 newFoward;
	newFoward.x = m_Foward.x * glm::cos(angle) + m_Foward.z * glm::sin(angle);
	newFoward.y = m_Foward.y;
	newFoward.z = -m_Foward.x * glm::sin(angle) + m_Foward.z * glm::cos(angle);

	m_Foward = glm::normalize(newFoward);

	// Recalculate Foward Vector
	m_Right = glm::normalize(glm::cross(m_Foward, m_Head));

	UpdateViewMatrix();
}

void Camera::Roll(float angle) {

	// Generate new m_Head position based on "angle" provided
	glm::vec3 newRight;
	newRight.x = m_Right.x * glm::cos(angle) - m_Right.y * glm::sin(angle);
	newRight.y = m_Right.x * glm::sin(angle) + m_Right.y * glm::cos(angle);
	newRight.z = m_Right.z;

	m_Right = glm::normalize(newRight);

	// Recalculate Foward Vector
	m_Head = glm::normalize(glm::cross(m_Right, m_Foward));

	UpdateViewMatrix();
}

void Camera::UpdatePosition(float deltaTime) {
	
	// Move forward
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_W) == GLFW_PRESS) {
		Walk(m_Speed * deltaTime);
	}
	// Move backward
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_S) == GLFW_PRESS) {
		Walk(-m_Speed * deltaTime);
	}
	// Strafe right
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_D) == GLFW_PRESS) {
		Strafe(-m_Speed * deltaTime);
	}
	// Strafe left
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_A) == GLFW_PRESS) {
		Strafe(m_Speed * deltaTime);
	}
}

void Camera::UpdateRotation(float deltaTime) {
}

void Camera::UpdateViewMatrix() {
	m_Renderer->SetCamView(
		m_Pos,
		m_Pos + m_Foward,
		m_Head
	);
}
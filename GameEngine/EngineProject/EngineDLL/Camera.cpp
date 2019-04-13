#include "Camera.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

Camera::Camera(Renderer* renderer, Window* window) {

	m_Renderer		= renderer;
	m_Window		= window;

	m_Pos			= glm::vec3(0, 0, 4);
	m_Rot			= glm::vec3(0);
	
	m_Foward		= glm::normalize(glm::vec3(0, 0, 0) - m_Pos);
	m_Right			= glm::normalize(glm::cross(glm::vec3(0,1,0), m_Foward));
	m_Head			= glm::normalize(glm::cross(m_Foward, m_Right));

	m_Speed			= 5.0f;
	m_RotationSpeed = 1.0f;

	// Store cursor's position by reference to local variable
	// Position is based on screen coordinates relative 
	// to the top-left corner of the window context
	glfwGetCursorPos(
		(GLFWwindow*)window->GetWindowPtr(),	// window context
		&m_PrevCursorPos.x,					// Get Cursor X Pos
		&m_PrevCursorPos.y					// Get Cursor Y Pos
	);
	m_CursorPos = m_PrevCursorPos;

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

void Camera::Pitch(float angle) {

	// Calculate new m_Head direction
	glm::vec3 newHead;
	newHead.x = m_Head.x;
	newHead.y = m_Head.y * glm::cos(angle) - m_Head.z * glm::sin(angle);
	newHead.z = m_Head.y * glm::sin(angle) + m_Head.z * glm::cos(angle);
	m_Head = glm::normalize(newHead);

	// Recalculate FOWARD Vector
	m_Foward = glm::normalize(glm::cross(m_Right, m_Head));
	
	UpdateViewMatrix();
}

void Camera::Yaw(float angle) {

	// Calculate new m_Foward direction
	glm::vec3 newFoward;
	newFoward.x =  m_Foward.x * glm::cos(angle) + m_Foward.z * glm::sin(angle);
	newFoward.y =  m_Foward.y;
	newFoward.z = -m_Foward.x * glm::sin(angle) + m_Foward.z * glm::cos(angle);
	m_Foward = glm::normalize(newFoward);

	// Recalculate RIGHT Vector
	m_Right = glm::normalize(glm::cross(m_Head, m_Foward));

	UpdateViewMatrix();
}

void Camera::Roll(float angle) {

	// Calculate new m_Right direction
	glm::vec3 newRight;
	newRight.x = m_Right.x * glm::cos(angle) - m_Right.y * glm::sin(angle);
	newRight.y = m_Right.x * glm::sin(angle) + m_Right.y * glm::cos(angle);
	newRight.z = m_Right.z;
	m_Right = glm::normalize(newRight);

	// Recalculate HEAD Vector
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

	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		Yaw(-m_RotationSpeed * deltaTime);
	}
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		Yaw(m_RotationSpeed * deltaTime);
	}
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_UP) == GLFW_PRESS) {
		Pitch(m_RotationSpeed * deltaTime);
	}
	if (glfwGetKey((GLFWwindow*)m_Window->GetWindowPtr(), GLFW_KEY_DOWN) == GLFW_PRESS) {
		Pitch(-m_RotationSpeed * deltaTime);
	}


	//UpdateCursorPos();
	//
	//// Look left
	//if (m_PrevCursorPos.x > m_CursorPos.x) {
	//	Yaw(m_RotationSpeed * deltaTime);
	//}
	//// Look right
	//if (m_PrevCursorPos.x < m_CursorPos.x) {
	//	Yaw(-m_RotationSpeed * deltaTime);
	//}
	//// Look up
	//if (m_PrevCursorPos.y < m_CursorPos.y) {
	//	Pitch(m_RotationSpeed * deltaTime);
	//}
	//// Look down
	//if (m_PrevCursorPos.y > m_CursorPos.y) {
	//	Pitch(-m_RotationSpeed * deltaTime);
	//}
	//m_PrevCursorPos = m_CursorPos;
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
		m_Pos + m_Foward,
		m_Head
	);
	m_Renderer->SetCamView(m_ViewMat);
}
#include "Camera.h"
#include "Transform.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

Camera::Camera(Renderer* renderer, Window* window) : Entity(renderer) {
	m_Renderer = renderer;
	m_Window = window;

	m_CameraTarget = glm::vec3(0, 0, 0);
	m_strafeSpeed	= 5.0f;
	m_RotationSpeed = 100.0f;
	m_transform->Yaw(180);
	
	UpdateViewMatrix();
}

void Camera::Update(float deltaTime) {
	Entity::Update(deltaTime);

	CheckForMovementInput(deltaTime);
	CheckForRotationInput(deltaTime);
	UpdateViewMatrix();
}

void Camera::CheckForMovementInput(float deltaTime) {
	float movementSpeed = m_strafeSpeed * deltaTime;
	GLFWwindow* window = (GLFWwindow*)m_Window->GetWindowPtr();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // Move forward
		m_transform->Walk(movementSpeed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // Move backward
		m_transform->Walk(-movementSpeed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // Strafe right
		m_transform->Strafe(movementSpeed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // Strafe left
		m_transform->Strafe(-movementSpeed);
}

void Camera::CheckForRotationInput(float deltaTime) {
	GLFWwindow* window = (GLFWwindow*)m_Window->GetWindowPtr();

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		m_transform->Yaw(-m_RotationSpeed * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		m_transform->Yaw(m_RotationSpeed * deltaTime);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		m_transform->Pitch(-m_RotationSpeed * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		m_transform->Pitch(m_RotationSpeed * deltaTime);

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		m_transform->Roll(m_RotationSpeed * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		m_transform->Roll(-m_RotationSpeed * deltaTime);
}

void Camera::UpdateViewMatrix() {
	m_ViewMat = glm::lookAt(
		m_transform->GetPosition(),
		m_transform->GetPosition() + m_transform->foward,
		m_transform->up
	);
	m_Renderer->SetCamView(m_ViewMat);
}
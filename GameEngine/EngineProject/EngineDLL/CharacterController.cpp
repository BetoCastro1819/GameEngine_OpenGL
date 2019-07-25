#include "CharacterController.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

void CharacterController::Update(float deltaTime) {

	float speed = 250.0f * deltaTime;

	glm::vec3 position = m_entity->GetPos();
	// Move forward
	if (glfwGetKey((GLFWwindow*)m_window->GetWindowPtr(), GLFW_KEY_UP) == GLFW_PRESS) {
		m_entity->SetPos(position.x, position.y + speed, position.z);
	}
	// Move backward
	if (glfwGetKey((GLFWwindow*)m_window->GetWindowPtr(), GLFW_KEY_DOWN) == GLFW_PRESS) {
		m_entity->SetPos(position.x, position.y - speed, position.z);
	}
	// Strafe right
	if (glfwGetKey((GLFWwindow*)m_window->GetWindowPtr(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		m_entity->SetPos(position.x + speed, position.y, position.z);
	}
	// Strafe left
	if (glfwGetKey((GLFWwindow*)m_window->GetWindowPtr(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		m_entity->SetPos(position.x - speed, position.y, position.z);
	}

	if (glfwGetKey((GLFWwindow*)m_window->GetWindowPtr(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose((GLFWwindow*)m_window->GetWindowPtr(), true);
	}

	//GLFW_KEY_UP;
	//GLFW_KEY_DOWN;
	//GLFW_KEY_LEFT;
	//GLFW_KEY_RIGHT;
	//GLFW_KEY_ESCAPE;
	//GLFW_KEY_SPACE;
}
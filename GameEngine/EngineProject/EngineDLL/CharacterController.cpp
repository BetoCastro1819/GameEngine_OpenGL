#include "CharacterController.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

CharacterController::CharacterController(Window* window, Entity* entity) {
	m_window = window;
	m_entity = entity;

	m_accelerationValue = 0.3f;
	m_maxSpeed = 5;
	m_dragCoefficient = -0.05f;
	m_gravityStrength = -0.2;

	m_velocity = glm::vec3(0);
	m_acceleration = glm::vec3(0);

	m_previousY = (int)m_entity->GetPos().y;

	m_canJump = true;
	m_holdJumpTime = 0.1f;
	m_jumpCountdown = 0.0f;
	m_jumpStrength = 3.0f;
}

void CharacterController::Update(float deltaTime) {
	UpdateVelocity(deltaTime);

	if (glfwGetKey((GLFWwindow*)m_window->GetWindowPtr(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose((GLFWwindow*)m_window->GetWindowPtr(), true);
	}
}

void CharacterController::UpdateVelocity(float deltaTime) {
	if (glfwGetKey((GLFWwindow*)m_window->GetWindowPtr(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		m_acceleration += World_Right * m_accelerationValue;
	}
	if (glfwGetKey((GLFWwindow*)m_window->GetWindowPtr(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		m_acceleration += -World_Right * m_accelerationValue;
	}


	if (glfwGetKey((GLFWwindow*)m_window->GetWindowPtr(), GLFW_KEY_SPACE) == GLFW_PRESS && m_canJump) {
		if (m_jumpCountdown > m_holdJumpTime) 
			m_canJump = false;

		m_acceleration += World_Up * m_jumpStrength;
		m_jumpCountdown += deltaTime;
	}

	if (m_entity->GetBoxCollider()->OnGroundCollision()) {
			m_canJump = true;
			m_jumpCountdown = 0.0f;
	}

	float currentSpeed = (m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y);
	glm::vec3 drag = m_velocity;
	m_acceleration += drag * m_dragCoefficient;

	if (!m_entity->GetBoxCollider()->OnGroundCollision()) {
		glm::vec3 gravity = World_Up * m_gravityStrength;
		m_acceleration += gravity;
	}

	m_velocity += m_acceleration;

	if (currentSpeed > m_maxSpeed * m_maxSpeed) {
		m_velocity = glm::normalize(m_velocity) * m_maxSpeed;
	}

	glm::vec3 position = m_entity->GetPos() + m_velocity;
	m_entity->SetPos(position.x, position.y, position.z);

	m_acceleration = glm::vec3(0);
}
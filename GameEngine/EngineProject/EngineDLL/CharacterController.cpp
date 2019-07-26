#include "CharacterController.h"
#include "Entity.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

CharacterController::CharacterController(Window* window, Entity* entity) {
	m_window = window;
	m_entity = entity;

	m_movementComp = new MovementComponent();
	m_movementComp->SetAcceleration(0.3f);
	m_movementComp->SetDragValue(0.05f);
	m_movementComp->SetMaxSpeed(5);

	m_canJump = true;
	m_holdJumpTime = 0.1f;
	m_jumpCountdown = 0.0f;
	m_jumpStrength = 3.0f;
}

CharacterController::~CharacterController() {
	if (m_movementComp != nullptr) delete m_movementComp;
}

void CharacterController::Update(float deltaTime) {
	CheckForInput(deltaTime);

	if (!m_entity->GetBoxCollider()->OnGroundCollision()) {
		m_movementComp->Applyforce(World_Up * m_movementComp->GetGravityValue());
	}
	m_movementComp->Update();
	m_entity->Translate(m_movementComp->GetVelocity());
}

void CharacterController::CheckForInput(float deltaTime) {
	MovementInput();
	JumpInput(deltaTime);
	CloseGameInput();
}

void CharacterController::MovementInput() {
	GLFWwindow* glfwWindow = (GLFWwindow*)m_window->GetWindowPtr();
	if (glfwGetKey(glfwWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		m_movementComp->AccelerateTowards(World_Right);
	}
	if (glfwGetKey(glfwWindow, GLFW_KEY_LEFT) == GLFW_PRESS) {
		m_movementComp->AccelerateTowards(-World_Right);
	}
}

void CharacterController::JumpInput(float deltaTime) {
	GLFWwindow* glfwWindow = (GLFWwindow*)m_window->GetWindowPtr();
	if (glfwGetKey(glfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS && m_canJump) {
		if (m_jumpCountdown > m_holdJumpTime) {
			m_canJump = false;
		}
		m_movementComp->Applyforce(World_Up * m_jumpStrength);
		m_jumpCountdown += deltaTime;
	}

	bool isGrounded = m_entity->GetBoxCollider()->OnGroundCollision();
	if (glfwGetKey(glfwWindow, GLFW_KEY_SPACE) == GLFW_RELEASE && !isGrounded) {
		m_canJump = false;
	}
	ResetJumpWhenGrounded();
}

void CharacterController::ResetJumpWhenGrounded() {
	if (m_entity->GetBoxCollider()->OnGroundCollision()) {
		m_canJump = true;
		m_jumpCountdown = 0.0f;
	}
}

void CharacterController::CloseGameInput() {
	if (glfwGetKey((GLFWwindow*)m_window->GetWindowPtr(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose((GLFWwindow*)m_window->GetWindowPtr(), true);
}
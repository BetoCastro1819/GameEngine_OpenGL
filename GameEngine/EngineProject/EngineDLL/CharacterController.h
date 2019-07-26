#pragma once
#include "Exports.h"
#include "Window.h"
#include "MovementComponent.h"

class Entity;

class ENGINEDLL_API CharacterController {
private:
	Window* m_window;
	Entity* m_entity;
	MovementComponent* m_movementComp;

	bool m_canJump;
	float m_holdJumpTime;
	float m_jumpCountdown;
	float m_jumpStrength;

	void CheckForInput(float deltaTime);
	void MovementInput();
	void JumpInput(float deltaTime);
	void ResetJumpWhenGrounded();

	void CloseGameInput();

public:
	CharacterController(Window* window, Entity* entity);

	~CharacterController();

	void Update(float deltaTime);
};


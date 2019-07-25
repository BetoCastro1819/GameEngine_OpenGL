#pragma once
#include "Exports.h"
#include "Window.h"
#include "Entity.h"

class ENGINEDLL_API CharacterController {
private:
	Window* m_window;
	Entity* m_entity;

	float m_accelerationValue;
	float m_maxSpeed;
	float m_dragCoefficient;
	float m_gravityStrength;

	bool m_canJump;
	float m_holdJumpTime;
	float m_jumpCountdown;
	float m_jumpStrength;

	int m_previousY;


	glm::vec3 m_velocity;
	glm::vec3 m_acceleration;

	void UpdateVelocity(float deltaTime);

public:
	CharacterController(Window* window, Entity* entity);

	~CharacterController() { }

	void Update(float deltaTime);
};


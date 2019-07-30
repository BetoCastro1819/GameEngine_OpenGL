#pragma once
#include "Exports.h"
#include "Entity.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class ENGINEDLL_API MovementComponent {
private:
	Entity* m_entity;

	glm::vec3 m_velocity;
	glm::vec3 m_acceleration;

	float m_accelerationValue;
	float m_maxSpeed;
	float m_dragCoefficient;
	float m_gravityStrength;

	void ClampVelocityAt(float maxSpeed);

public:
	MovementComponent(Entity* entity);
	~MovementComponent() { }

	void Update();
	void Applyforce(const glm::vec3& force) { m_acceleration += force; }

	void SetAcceleration(float acceleration) { m_accelerationValue = acceleration; }
	void SetDragValue(float drag) { m_dragCoefficient = drag; }
	void SetMaxSpeed(float maxSpeed) { m_maxSpeed = maxSpeed; }
	void SetVelocity(const glm::vec3& velocity) { m_velocity = velocity; }

	glm::vec3 GetVelocity() const { return m_velocity; }

	void AccelerateTowards(const glm::vec3& dir) { m_acceleration += dir * m_accelerationValue; }
};


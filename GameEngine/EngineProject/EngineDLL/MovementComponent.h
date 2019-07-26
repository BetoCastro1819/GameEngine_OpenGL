#pragma once
#include "Exports.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class ENGINEDLL_API MovementComponent {
private:
	glm::vec3 m_velocity;
	glm::vec3 m_acceleration;

	float m_accelerationValue;
	float m_maxSpeed;
	float m_dragCoefficient;
	float m_gravityStrength;

	void ClampVelocityAt(float maxSpeed);

public:
	MovementComponent();
	~MovementComponent() { }

	void Update();
	void Applyforce(const glm::vec3& force) { m_acceleration += force; }

	void SetAcceleration(float acceleration) { m_accelerationValue = acceleration; }
	void SetDragValue(float drag) { m_dragCoefficient = drag; }
	void SetMaxSpeed(float maxSpeed) { m_maxSpeed = maxSpeed; }

	float GetGravityValue() const { return m_gravityStrength; }
	glm::vec3  GetVelocity() const { return m_velocity; }

	void AccelerateTowards(const glm::vec3& dir) { m_acceleration += dir * m_accelerationValue; }
};


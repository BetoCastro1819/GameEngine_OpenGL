#include "MovementComponent.h"

MovementComponent::MovementComponent() {
	m_accelerationValue = 0.3f;
	m_maxSpeed = 5;
	m_dragCoefficient = -0.05f;
	m_gravityStrength = -0.2;

	m_velocity = glm::vec3(0);
	m_acceleration = glm::vec3(0);
}

void MovementComponent::Update() {
	m_acceleration += m_velocity * -m_dragCoefficient;
	m_velocity += m_acceleration;
	ClampVelocityAt(m_maxSpeed);
	m_acceleration = glm::vec3(0);
}

void MovementComponent::ClampVelocityAt(float maxSpeed) {
	float currentSpeed = (m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y);
	if (currentSpeed > m_maxSpeed * m_maxSpeed) {
		m_velocity = glm::normalize(m_velocity) * m_maxSpeed;
	}
}
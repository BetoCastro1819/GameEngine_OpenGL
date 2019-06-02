#include "Entity.h"

Entity::Entity(Renderer* renderer)	 {
	m_renderer = renderer;
	
	m_modelMatrix = glm::mat4(1.0f);

	m_translateMatrix = glm::mat4(1.0f);
	m_rotateMatrix = glm::mat4(1.0f);
	m_scaleMatrix = glm::mat4(1.0f);

	m_position[0] = m_position[1] = m_position[2] = 0.0f;
	m_scale[0] = m_scale[1] = m_scale[2] = 1.0f;
	m_rotation[0] = m_rotation[1] = m_rotation[2] = 0.0f;

	m_modelMatrix = glm::mat4(1.0f);
}

Entity::~Entity() {
}

void Entity::SetPos(float x, float y, float z) {
	m_position[0] = x;
	m_position[1] = y;
	m_position[2] = z;

	m_translateMatrix = glm::translate(glm::mat4(1.0f), m_position);
	UpdateModelMatrix();
}

void Entity::SetScale(float x, float y, float z) {
	m_scale[0] = x;
	m_scale[1] = y;
	m_scale[2] = z;

	m_scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);
	UpdateModelMatrix();
}

void Entity::SetRotX(float angle) {
	m_rotation[0] = angle;
	m_rotation[1] = 0;
	m_rotation[2] = 0;

	m_rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_rotation);
	UpdateModelMatrix();
}

void Entity::SetRotY(float angle) {
	m_rotation[0] = 0;
	m_rotation[1] = angle;
	m_rotation[2] = 0;

	m_rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_rotation);
	UpdateModelMatrix();
}

void Entity::SetRotZ(float angle) {
	m_rotation[0] = 0;
	m_rotation[1] = 0;
	m_rotation[2] = angle;

	m_rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_rotation);
	UpdateModelMatrix();
}
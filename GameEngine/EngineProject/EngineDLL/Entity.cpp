#include "Entity.h"

Entity::Entity(Renderer* renderer)	 {
	_renderer = renderer;
	
	_modelMatrix = glm::mat4(1.0f);

	_translateMatrix = glm::mat4(1.0f);
	_rotateMatrix = glm::mat4(1.0f);
	_scaleMatrix = glm::mat4(1.0f);

	m_Position[0] = m_Position[1] = m_Position[2] = 0.0f;
	m_Scale[0] = m_Scale[1] = m_Scale[2] = 1.0f;
	m_Rotation[0] = m_Rotation[1] = m_Rotation[2] = 0.0f;
}

Entity::~Entity() {
}

void Entity::SetPos(float x, float y, float z) {
	m_Position[0] = x;
	m_Position[1] = y;
	m_Position[2] = z;

	_translateMatrix = glm::translate(glm::mat4(1.0f), m_Position);
	UpdateModelMatrix();
}

void Entity::SetScale(float x, float y, float z) {
	m_Scale[0] = x;
	m_Scale[1] = y;
	m_Scale[2] = z;

	_scaleMatrix = glm::scale(glm::mat4(1.0f), m_Scale);
	UpdateModelMatrix();
}

void Entity::SetRotX(float angle) {
	m_Rotation[0] = angle;
	m_Rotation[1] = 0;
	m_Rotation[2] = 0;

	_rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_Rotation);
	UpdateModelMatrix();
}

void Entity::SetRotY(float angle) {
	m_Rotation[0] = 0;
	m_Rotation[1] = angle;
	m_Rotation[2] = 0;

	_rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_Rotation);
	UpdateModelMatrix();
}

void Entity::SetRotZ(float angle) {
	m_Rotation[0] = 0;
	m_Rotation[1] = 0;
	m_Rotation[2] = angle;

	_rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_Rotation);
	UpdateModelMatrix();
}

void Entity::UpdateModelMatrix() {
	_modelMatrix = _translateMatrix * _rotateMatrix * _scaleMatrix;
}
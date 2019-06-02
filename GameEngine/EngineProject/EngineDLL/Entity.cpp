#include "Entity.h"

Entity::Entity(Renderer* renderer)	 {
	m_renderer = renderer;
}

Entity::~Entity() {
}

void Entity::SetPos(float x, float y, float z) {
	m_transform.SetPosition(glm::vec3(x, y, z));
	UpdateModelMatrix();
}

void Entity::SetScale(float x, float y, float z) {
	m_transform.SetScale(glm::vec3(x, y, z));
	UpdateModelMatrix();
}

void Entity::SetRotX(float angle) {
	m_transform.SetRotX(angle);
	UpdateModelMatrix();
}

void Entity::SetRotY(float angle) {
	m_transform.SetRotY(angle);
	UpdateModelMatrix();
}

void Entity::SetRotZ(float angle) {
	m_transform.SetRotZ(angle);
	UpdateModelMatrix();
}
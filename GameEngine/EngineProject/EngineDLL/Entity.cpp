#include "Entity.h"
#include "Transform.h"

Entity::Entity(Renderer* renderer)	 {
	m_renderer = renderer;
	m_transform = new Transform(this);
	AddComponent(m_transform);
	m_name = "";
}

Entity::~Entity() {
	if (m_transform != nullptr) delete m_transform;
}

void Entity::Update(float deltaTime) {
	SceneNode::Update(deltaTime);
}
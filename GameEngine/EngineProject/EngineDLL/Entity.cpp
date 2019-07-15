#include "Entity.h"
#include "Transform.h"

Entity::Entity(Renderer* renderer)	 {
	m_renderer = renderer;
	m_transform = new Transform(this);
	AddComponent(m_transform);
}

Entity::~Entity() {
	if (m_transform != nullptr) delete m_transform;
}

void Entity::Update(float deltaTime) {
	m_renderer->DrawCube(GetTransform()->GetboundingBox().vertices);
	SceneNode::Update(deltaTime);
}
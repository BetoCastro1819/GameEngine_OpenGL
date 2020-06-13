#include "Entity.h"
#include "../../components/Transform.h"
#include "../../rendering/Renderer.h"

Entity::Entity(Renderer* renderer)	 {
	m_renderer = renderer;
	m_transform = new Transform(this);
	AddComponent(m_transform);
	m_isVisible = true;
}

Entity::~Entity() {
	if (m_transform != nullptr) delete m_transform;
}

void Entity::Update(float deltaTime) {
	SceneNode::Update(deltaTime);
}

void Entity::DrawBoundingBox() {
	m_renderer->DrawCube(m_transform->GetBoundingBox()->vertices);
}
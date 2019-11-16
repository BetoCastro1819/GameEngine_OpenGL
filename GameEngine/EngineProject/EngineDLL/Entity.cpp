#include "Entity.h"
#include "Transform.h"

Entity::Entity(Renderer* renderer)	 {
	m_renderer = renderer;
	m_transform = new Transform(this);
	AddComponent(m_transform);
	m_isInsideFrustrum = true;
}

Entity::~Entity() {
	if (m_transform != nullptr) delete m_transform;
}

void Entity::Update(float deltaTime) {
	//m_renderer->DrawCube(GetTransform()->GetboundingBox().vertices);
	if (m_isInsideFrustrum)
		SceneNode::Update(deltaTime);
}
#include "Entity.h"
#include "Transform.h"

Entity::Entity(Renderer* renderer)	 {
	m_renderer = renderer;
	m_transform = new Transform(this);
}

Entity::~Entity() {
	if (m_transform != nullptr) delete m_transform;
}

void Entity::Update(float deltaTime) {
	for (std::list<Component*>::iterator iter = m_componentList.begin();
		iter != m_componentList.end(); iter++) {
		(*iter)->Update(deltaTime);
	}
	SceneNode::Update(deltaTime);
}

//void Entity::SetPos(float x, float y, float z) {
//	m_transform->SetPosition(glm::vec3(x, y, z));
//	UpdateModelMatrix();
//}
//
//void Entity::SetScale(float x, float y, float z) {
//	m_transform->SetScale(glm::vec3(x, y, z));
//	UpdateModelMatrix();
//}
//
//void Entity::SetRotX(float angle) {
//	m_transform->SetRotX(angle);
//	UpdateModelMatrix();
//}
//
//void Entity::SetRotY(float angle) {
//	m_transform->SetRotY(angle);
//	UpdateModelMatrix();
//}
//
//void Entity::SetRotZ(float angle) {
//	m_transform->SetRotZ(angle);
//	UpdateModelMatrix();
//}
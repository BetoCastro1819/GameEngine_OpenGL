#include "Component.h"

Component::Component(Entity* entity) {
	SetType(ComponentType::DEFAULT);
	m_entity = entity;
}

Component::~Component() {
}

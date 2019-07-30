#include "BoxCollider.h"
#include "Entity.h"

BoxCollider::BoxCollider(double boxWidth, double boxHeight) {
	_boxWidth = boxWidth;
	_boxHeight = boxHeight;

	m_groundCollision = false;

	m_collisionFlag.top = false;
	m_collisionFlag.bottom = false;
	m_collisionFlag.left = false;
	m_collisionFlag.right = false;

	m_collidingEntity = nullptr;
}

BoxCollider::~BoxCollider() {
}

Entity* BoxCollider::GetCollidingEntity() const {
	return m_collidingEntity;
}

void BoxCollider::SetCollidingEntity(Entity* entity) {
	m_collidingEntity = entity;
}
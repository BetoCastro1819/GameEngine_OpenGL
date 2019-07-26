#include "BoxCollider.h"
#include "Entity.h"

BoxCollider::BoxCollider(double boxWidth, double boxHeight) {
	_boxWidth = boxWidth;
	_boxHeight = boxHeight;

	m_groundCollision = false;
}

BoxCollider::~BoxCollider() {
}

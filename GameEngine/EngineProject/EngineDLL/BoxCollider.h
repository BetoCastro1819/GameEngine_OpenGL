#pragma once
#include "Exports.h"

class Entity;

class ENGINEDLL_API BoxCollider {
private:
	Entity* m_collidingEntity;
	double _boxWidth;
	double _boxHeight;

	bool m_groundCollision;

	struct CollisionFlag {
		bool top;
		bool bottom;
		bool left;
		bool right;
	} m_collisionFlag;

public:
	BoxCollider(double boxWidth, double boxHeight);
	~BoxCollider();

	Entity* GetCollidingEntity() const;
	void SetCollidingEntity(Entity* enity);

	double GetBoxWidth() { return _boxWidth; }
	void SetBoxWidth(double width) { _boxWidth = width; }

	double GetBoxHeight() { return _boxHeight; }
	void SetBoxHeight(double height) { _boxHeight = height; }

	CollisionFlag GetCollisionFlag() const { return m_collisionFlag; }
	void SetCollisionFlag_top(bool isOnCollision) { m_collisionFlag.top = isOnCollision; }
	void SetCollisionFlag_bottom(bool isOnCollision) { m_collisionFlag.bottom = isOnCollision; }
	void SetCollisionFlag_left(bool isOnCollision) { m_collisionFlag.left = isOnCollision; }
	void SetCollisionFlag_right(bool isOnCollision) { m_collisionFlag.right = isOnCollision; }
};



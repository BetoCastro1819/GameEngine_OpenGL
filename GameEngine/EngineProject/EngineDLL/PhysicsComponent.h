#pragma once
#include "Exports.h"
#include "Component.h"
#include "PxPhysicsAPI.h"

class Entity;

class ENGINEDLL_API PhysicsComponent : public Component {
public:
	PhysicsComponent(Entity* entity);
	~PhysicsComponent();

	void Update(float deltaTime) override { }
};


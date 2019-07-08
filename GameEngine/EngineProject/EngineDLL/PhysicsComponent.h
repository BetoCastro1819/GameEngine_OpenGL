#pragma once
#include "Exports.h"
#include "Component.h"
//#include "PxPhysicsAPI.h"

class Entity;

//namespace physx
//{
//	class PxScene;
//}

class ENGINEDLL_API PhysicsComponent : public Component {
private:
	//physx::PxScene* m_scene;

public:
	PhysicsComponent(Entity* entity);
	~PhysicsComponent();

	void Update(float deltaTime) override { }
};


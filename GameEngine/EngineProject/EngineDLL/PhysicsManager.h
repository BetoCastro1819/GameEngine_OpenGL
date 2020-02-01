#pragma once

#include <iostream>
#include "Exports.h"
#include "glm/glm.hpp"

const float GRAVITY = -0.0f;

namespace physx
{
	class PxFoundation;
	class PxPhysics;
	class PxCooking;
	class PxScene;
	class PxActor;
	class PxTransform;
	class PxRigidActor;
	class PxCapsuleGeometry;
	class PxMaterial;
	class PxHeightField;
	class PxHeightFieldDesc;
	class PxSimulationEventCallback;
}

class ENGINEDLL_API PhysicsManager {
private:
	static PhysicsManager* m_instance;

	physx::PxFoundation* m_pxFoundation;
	physx::PxPhysics* m_pxPhysics;
	physx::PxCooking* m_pxCooking;
	physx::PxScene* m_pxScene;

	PhysicsManager();
	~PhysicsManager();
public:
	static PhysicsManager* getInstance();
	void deleteInstance();

	bool start(glm::vec3 gravity, unsigned int numberOfThreads);
	void stop();

	void simulate(float deltaTime);
	void fetchSimulationResults();

	void addActor(physx::PxActor* actor);
	void removeActor(physx::PxActor* actor);

	void setCurrentSceneGravity(glm::vec3 gravity);
	void setSimulationEventCallback(physx::PxSimulationEventCallback* simulationCallback);

	physx::PxMaterial* createPhysicsMaterial(float staticFriction, float dynamicFriction, float restitution);
	physx::PxRigidActor* createRigidActor(physx::PxTransform pxTransform, bool isStatic);
	physx::PxHeightField* createHeighField(physx::PxHeightFieldDesc hfDesc);
};


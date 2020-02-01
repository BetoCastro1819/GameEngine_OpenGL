#pragma once
#include <iostream>
#include <PxPhysicsAPI.h>

class SimulationEventCallback : public physx::PxSimulationEventCallback {
private:
	physx::PxRigidActor* m_pxRigidActor;

public:
	SimulationEventCallback(physx::PxRigidActor* pxRigidActor);
	~SimulationEventCallback();

	void onContact(const physx::PxContactPairHeader& pairHeader, 
				   const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override;

	void onWake(physx::PxActor** actors, physx::PxU32 count) override {}
	void onConstraintBreak(physx::PxConstraintInfo *constraints, physx::PxU32 count) override {}
	void onSleep(physx::PxActor** actors, physx::PxU32 count) override {}
	void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override {}
	void onAdvance(const physx::PxRigidBody *const *bodyBuffer, const physx::PxTransform *poseBuffer, const physx::PxU32 count) override {}
};


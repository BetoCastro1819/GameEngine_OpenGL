#include "SimulationEventCallback.h"



SimulationEventCallback::SimulationEventCallback(physx::PxRigidActor* pxRigidActor) : physx::PxSimulationEventCallback() {
	m_pxRigidActor = pxRigidActor;
}

SimulationEventCallback::~SimulationEventCallback() {
}

void SimulationEventCallback::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) {
	for (int i = 0; i < nbPairs; i++) {
		const physx::PxContactPair& contactPair = pairs[i];

		if (contactPair.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND) {
			if (pairHeader.actors[0] == m_pxRigidActor || pairHeader.actors[1] == m_pxRigidActor) {
				//printf("Collision detected.\n");
			}
		}
	}
}

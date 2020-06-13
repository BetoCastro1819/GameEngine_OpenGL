#include "SimulationEventCallback.h"
#include "../scene_graph/entities/Entity.h"

SimulationEventCallback::SimulationEventCallback(Entity* entity, physx::PxRigidActor* pxRigidActor) : physx::PxSimulationEventCallback() {
	m_pxRigidActor = pxRigidActor;
	m_entity = entity;
}

SimulationEventCallback::~SimulationEventCallback() {
}

void SimulationEventCallback::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) {
	for (int i = 0; i < nbPairs; i++) {
		const physx::PxContactPair& contactPair = pairs[i];

		if (contactPair.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND) {
			if (pairHeader.actors[0] == m_pxRigidActor || pairHeader.actors[1] == m_pxRigidActor) {
				physx::PxRigidDynamic* rigidDynamic = (physx::PxRigidDynamic*)m_pxRigidActor;
				m_entity->OnContact(rigidDynamic->getLinearVelocity().magnitude());
			}
		}
	}
}

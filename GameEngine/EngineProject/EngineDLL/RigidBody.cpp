#include "RigidBody.h"
#include "PhysicsManager.h"
#include "Transform.h"
#include "BoxCollider.h"
#include <PxPhysicsAPI.h>

RigidBody::RigidBody(Entity* entity) : Component(entity) {
	m_entity = entity;
	m_pxRigidActor = NULL;
	m_pxShape = NULL;
	m_pxMaterial = NULL;
}


RigidBody::~RigidBody() {
	if (m_pxRigidActor) {
		if (m_pxMaterial)
			m_pxMaterial->release();

		if (m_pxShape)
			m_pxRigidActor->detachShape(*m_pxShape);

		PhysicsManager::getInstance()->removeActor(m_pxRigidActor);
	}
}

void RigidBody::Update(float deltaTime) {
	physx::PxTransform pxTransform = m_pxRigidActor->getGlobalPose();
	physx::PxVec3 pxPosition = pxTransform.p;
	physx::PxQuat pxRotation = pxTransform.q;

	glm::vec3 position = glm::vec3(pxPosition.x, pxPosition.y, pxPosition.z);
	glm::vec4 rotation(pxRotation.x, pxRotation.y, pxRotation.z, pxRotation.w);

	m_transform->SetPosition(position);
	m_transform->ChangeRotationMatrix(rotation);
}

void RigidBody::CreateRigidBody(bool isStatic, float mass, float staticFriction, 
								float dynamicFriction, float restitution,
								glm::vec3 colliderOffset) 
{
	m_transform = m_entity->GetTransform();
	m_isStatic = isStatic;

	glm::vec3 position = m_transform->GetPosition();
	glm::vec3 rotation = m_transform->GetRotation();

	glm::vec4 rotQuat = Transform::ConvertToQuaternion(rotation.x, rotation.y, rotation.z);

	physx::PxVec3 pxPosition(position.x, position.y, position.z);
	physx::PxQuat pxRotation(rotQuat.x, rotQuat.y, rotQuat.z, rotQuat.w);

	physx::PxVec3 localOffset(colliderOffset.x, colliderOffset.y, colliderOffset.z);
	physx::PxQuat localRot(physx::PxHalfPi, physx::PxVec3(0.0f, 0.0f, 1.0f));
	physx::PxTransform pxTransform(pxPosition, pxRotation);
	physx::PxTransform realtivePose(localOffset, localRot);


	float halfWidth, halfHeight, halfDepth;

	glm::vec3 maxVector = m_transform->GetBoundingBox()->maxVertex;
	glm::vec3 minVector = m_transform->GetBoundingBox()->minVertex;

	halfWidth  = (maxVector.x - minVector.x) * 0.5f;
	halfHeight = (maxVector.y - minVector.y) * 0.5f;
	halfDepth  = (maxVector.z - minVector.z) * 0.5f;

	float scaleX = m_transform->GetScale().x;
	float scaleY = m_transform->GetScale().y;
	float scaleZ = m_transform->GetScale().z;

	physx::PxGeometry* pxGeometry = new physx::PxBoxGeometry(halfHeight * scaleY, halfWidth * scaleX, halfDepth * scaleZ);


	PhysicsManager* physicsManager = PhysicsManager::getInstance();
	
	m_pxRigidActor = physicsManager->createRigidActor(pxTransform, m_isStatic);
	m_pxMaterial = physicsManager->createPhysicsMaterial(staticFriction, dynamicFriction, restitution);
	m_pxShape = physx::PxRigidActorExt::createExclusiveShape(*m_pxRigidActor, *pxGeometry, *m_pxMaterial);
	m_pxShape->setLocalPose(realtivePose);

	if (!m_isStatic) {
		physx::PxRigidDynamic* rigidDynamic = (physx::PxRigidDynamic*)m_pxRigidActor;
		rigidDynamic->setMassSpaceInertiaTensor(physx::PxVec3(1.0f, 1.0f, 1.0f));
		physx::PxRigidBodyExt::setMassAndUpdateInertia(*rigidDynamic, (physx::PxReal)mass);
	}

	physicsManager->addActor(m_pxRigidActor);
}

void RigidBody::AddForce(glm::vec3 force, ForceType forceType) {
	if (!m_isStatic) {
		physx::PxRigidDynamic* rigidDynamic = (physx::PxRigidDynamic*)m_pxRigidActor;
		physx::PxVec3 pxForce(force.x, force.y, force.z);

		rigidDynamic->addForce(pxForce, (physx::PxForceMode::Enum)forceType);
	}
}

void RigidBody::AddTorque(glm::vec3 torque, ForceType forceType) {

}

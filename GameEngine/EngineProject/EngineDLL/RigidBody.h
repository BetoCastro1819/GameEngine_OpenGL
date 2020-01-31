#pragma once
#include <iostream>
#include "Exports.h"
#include "Component.h"
#include "glm/glm.hpp"

namespace physx 
{
	struct PxForceMode;
	class PxRigidActor;
	class PxShape;
	class PxMaterial;
}

class BoxCollider;
class Transform;

enum ForceType {
	FORCE,
	IMPULSE,
	VELOCITY_CHANGE,
	ACCELERATION
};


class ENGINEDLL_API RigidBody : public Component {
private:
	Transform* m_transform;

	physx::PxRigidActor* m_pxRigidActor;
	physx::PxShape* m_pxShape;
	physx::PxMaterial* m_pxMaterial;

	bool m_isStatic;


public:
	RigidBody(Entity* entity);
	~RigidBody();

	void Update(float deltaTime) override;

	void CreateRigidBody(bool isStatic, float mass, float staticFriction, 
						 float dynamicFriction, float restitution, 
						 glm::vec3 colliderOffset = glm::vec3(0.0f));

	void AddForce(glm::vec3 force, ForceType forceType);
	void AddTorque(glm::vec3 torque, ForceType forceType);
};


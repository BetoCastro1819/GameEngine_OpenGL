#pragma once
#include "../../misc/Exports.h"
#include "Entity.h"

#include "glm/glm.hpp"

class Material;
class Mesh;
class RigidBody;
class SimulationEventCallback;

class ENGINEDLL_API Suzzane : public Entity {
private:
	Material* m_material;
	Mesh* m_mesh;
	RigidBody* m_rigidBody;

	SimulationEventCallback* m_simulationCallback;

	bool m_hasLanded;
	float m_maxVelocityToLand;

	float m_fuel;
	float m_fuelConsumptionRate;

	void HandleInput(float deltaTime);
	void ActivateThrust(float deltaTime);
	void Rotate(const glm::vec3& torque);

public:
	Suzzane(Renderer* renderer, bool isStatic, glm::vec3 startPosition = glm::vec3(0));
	~Suzzane();

	void Update(float deltaTime) override;
	void OnContact(float velocityOfImpact) override;
};


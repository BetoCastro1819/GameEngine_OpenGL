#pragma once
#include "Exports.h"
#include "Entity.h"

class Material;
class Mesh;
class RigidBody;

class ENGINEDLL_API Suzzane : public Entity {
private:
	Material* m_material;
	Mesh* m_mesh;
	RigidBody* m_rigidBody;

	void HandleInput(float deltaTime);
	void ActivateThrust(float deltaTime);
	void Rotate(const glm::vec3& torque);

public:
	Suzzane(Renderer* renderer);
	~Suzzane();

	void Update(float deltaTime) override;
};


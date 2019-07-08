#pragma once
#include "Exports.h"
#include "Entity.h"

class Material;
class Mesh;
class PhysicsComponent;

class ENGINEDLL_API Suzzane : public Entity {
private:
	Material* m_material;
	Mesh* m_mesh;
	PhysicsComponent* m_physicsComponent;

public:
	Suzzane(Renderer* renderer);
	~Suzzane();

	void Update(float deltaTime) override;
};


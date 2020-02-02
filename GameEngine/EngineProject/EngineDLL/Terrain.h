#pragma once
#include "Exports.h"
#include "Entity.h"

class Material;
class Mesh;
class RigidBody;

class ENGINEDLL_API Terrain : public Entity {
private:
	Material* m_material;
	Mesh* m_mesh;
	RigidBody* m_rigidBody;

public:
	Terrain(Renderer* renderer, glm::vec3 startPosition = glm::vec3(0));
	~Terrain();

	void Update(float deltaTime) override;
};


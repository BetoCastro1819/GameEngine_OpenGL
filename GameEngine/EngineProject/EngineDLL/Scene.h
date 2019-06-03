#pragma once
#include "Exports.h"
#include "Entity.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Camera.h"

class ENGINEDLL_API Scene : public Entity {
private:
	Camera* m_camera;
	Material* m_material;
	Mesh* m_meshParent;
	Mesh* m_meshChild;
	Mesh* m_meshChild2;
	
	float m_rotationSpeed;

public:
	Scene(Renderer* renderer, Camera* camera);
	~Scene();

	void Update(float deltaTime) override;
	bool Start();
};


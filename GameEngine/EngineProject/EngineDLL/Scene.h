#pragma once
#include "Exports.h"
#include "Entity.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Camera.h"
#include "Suzzane.h"

class ENGINEDLL_API Scene : public Entity {
private:
	Camera* m_camera;
	Suzzane* m_cubeTest;

	float m_rotationSpeed;

public:
	Scene(Renderer* renderer, Camera* camera);
	~Scene();

	void Update(float deltaTime) override;
	bool Start();
};


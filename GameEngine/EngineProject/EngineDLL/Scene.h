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
	Suzzane* m_suzanne;
	Suzzane* m_suzanne_1;

	std::vector<SceneNode*> m_entities;

	float m_rotationSpeed;

	void FillVectorWithEntitiesInScene();
	bool is_bsp_plane(Entity* entity) const;

public:
	Scene(Renderer* renderer, Camera* camera);
	~Scene();

	void Update(float deltaTime) override;
	bool Start();
};


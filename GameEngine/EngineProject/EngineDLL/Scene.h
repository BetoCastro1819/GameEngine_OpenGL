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

	std::vector<SceneNode*> m_entities;

	void FillVectorWithEntitiesInScene();
	bool is_bsp_plane(Entity* entity) const;


public:
	Scene(Renderer* renderer, Camera* camera);
	~Scene();

	void Update(float deltaTime) override;
	bool Start();
};


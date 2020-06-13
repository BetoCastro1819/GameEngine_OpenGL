#pragma once
#include "../../misc/Exports.h"
#include "Entity.h"

class Camera;
class Suzzane;
class Terrain;
class LandingPad;

class ENGINEDLL_API Scene : public Entity {
private:
	Camera* m_camera;
	Suzzane* m_suzanne;
	Terrain* m_terrain;
	LandingPad* m_landingPad;

	std::vector<SceneNode*> m_entities;

	void FillVectorWithEntitiesInScene();
	bool is_bsp_plane(Entity* entity) const;

public:
	Scene(Renderer* renderer, Camera* camera);
	~Scene();

	void Update(float deltaTime) override;
	bool Start();
};
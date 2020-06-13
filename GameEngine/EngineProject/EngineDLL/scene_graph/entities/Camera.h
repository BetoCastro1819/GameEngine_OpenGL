#pragma once
#include <iostream>
#include <vector>

#include "../../misc/Exports.h"
#include "../../misc/Plane.h"
#include "Entity.h"

//#include "../../core/Window.h"
//#include "../../components/Transform.h"
//#include "../../rendering/Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Renderer;
class Plane;
class Window;

enum ClippingPlane {
	Left	= 0,
	Right	= 1,
	Top		= 2,
	Bottom	= 3,
	Near	= 4,
	Far		= 5
};

class ENGINEDLL_API Camera  : public Entity {
private:
	Window* m_Window;

	Plane m_frustrumPlanes[6];

	std::vector<Entity*> m_entities;
	std::vector<Entity*> m_currentlyVisibleEntities;
	std::vector<Entity*> m_previouslyVisibleEntities;

	std::vector<Plane> m_bspPlanes;

	float zNear;
	float zFar;
	float fov;
	float aspectRatio;
	float angleAccumulator;
	float radiusFromTarget;

	glm::vec3 m_CameraTarget;
	glm::mat4 m_ViewMat;
	
	float m_strafeSpeed;
	float m_RotationSpeed;

	void UpdateViewMatrix();
	void CheckForMovementInput(float deltaTime);
	void CheckForRotationInput(float deltaTime);
	void UpdateFrustrumPlanes();

	bool isInsideFrustrum(Plane& plane, Entity* entity);
	bool isBehindBSPPlane(const Entity* entity, const Plane& bspPlane) const;

public:
	Camera(Renderer* renderer, Window* window);
	~Camera() { }
	
	void Update(float deltaTime) override;

	void TestForVisibility(Entity* entity, int index);

	void AddEntity(Entity* entity) { 
		m_entities.push_back(entity);
		//printf("\nNumber of entities in camera %d\n", m_entities.size());
	}
	void AddPlane(Plane plane) { 
		m_bspPlanes.push_back(plane); 
		//printf("\nNumber of bsp planes: %d\n", m_bspPlanes.size());
	}

	Window* GetWindow() { return m_Window; }
};


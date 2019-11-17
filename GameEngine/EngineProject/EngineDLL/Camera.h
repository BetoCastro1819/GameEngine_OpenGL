#pragma once
#include <iostream>

#include "Exports.h"
#include "Window.h"
#include "Renderer.h"
#include "Entity.h"
#include "Transform.h"

// GLM -> math library
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

	struct Plane {
		float a, b, c, d;
	} m_planes[6];

	float zNear;
	float zFar;
	float fov;
	float aspectRatio;

	glm::vec3 m_CameraTarget;
	glm::mat4 m_ViewMat;
	
	float m_strafeSpeed;
	float m_RotationSpeed;

	void UpdateViewMatrix();
	void CheckForMovementInput(float deltaTime);
	void CheckForRotationInput(float deltaTime);
	void UpdateFrustrumPlanes();

	bool isInsideFrustrum(Plane& plane, Entity* entity);

	// Plane stuff
	void NormalizePlane(Plane& plane);
	float SignedDistanceToPlane(const Plane& plane, const glm::vec3& point) const;
	glm::vec3 ClosestPointOnPlaneFromPosition(const Plane& plane, const glm::vec3& position) const;
	Plane CreatePlaneFromPointAndNormal(const glm::vec3& point, const glm::vec3& normal);

public:
	Camera(Renderer* renderer, Window* window);
	~Camera() { }
	
	void Update(float deltaTime) override;
	void DrawFrustrumPlanes();

	void TestForFrustrumCulling(Entity* entity);
};


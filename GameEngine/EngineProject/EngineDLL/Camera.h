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

struct Plane {
	glm::vec3 bottomLeft;
	glm::vec3 bottomRight;
	glm::vec3 topRight;
	glm::vec3 topLeft;

	glm::vec3 normal;
};

//struct ClippingPlane {
//	Plane far;
//	Plane near;
//	Plane left;
//	Plane right;
//	Plane top;
//	Plane bottom;
//};

class ENGINEDLL_API Camera  : public Entity {
private:
	Window* m_Window;

	Plane plane_near;
	Plane plane_far;
	Plane plane_top;
	Plane plane_bottom;
	Plane plane_left;
	Plane plane_right;

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

	void UpdateClippingPlanes();
	bool isBehindPlane(Plane plane, Entity* entity) const;

public:
	Camera(Renderer* renderer, Window* window);
	~Camera() { }
	
	void Update(float deltaTime) override;
	void DrawFrustrumPlanes();

	void TestForFrustrumCulling(Entity* entity);
};


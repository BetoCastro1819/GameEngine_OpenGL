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

class ENGINEDLL_API Camera  : public Entity {
private:
	Renderer* m_Renderer;
	Window* m_Window;

	glm::vec3 m_CameraTarget;
	glm::mat4 m_ViewMat;
	
	float m_strafeSpeed;
	float m_RotationSpeed;

	void UpdateViewMatrix();
	void CheckForMovementInput(float deltaTime);
	void CheckForRotationInput(float deltaTime);

public:
	Camera(Renderer* renderer, Window* window);
	~Camera() { }
	
	void Update(float deltaTime) override;
};


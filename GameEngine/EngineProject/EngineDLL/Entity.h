#pragma once
#include "Renderer.h"
#include "BoxCollider.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// World unit vectors
const glm::vec3 World_Right		= glm::vec3(1, 0, 0);
const glm::vec3 World_Up		= glm::vec3(0, 1, 0);
const glm::vec3 World_Foward	= glm::vec3(0, 0, 1);

class ENGINEDLL_API Entity {
protected:
	Renderer* m_renderer;
	BoxCollider* m_collider;

	// Transform vectors
	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec3 m_Rotation;

	// Unit vectors for local direction
	glm::vec3 m_Foward;
	glm::vec3 m_Right;
	glm::vec3 m_Up;

	// Transform matrices
	glm::mat4 m_ModelMat;
	glm::mat4 m_TranslateMat;
	glm::mat4 m_RotateMat;
	glm::mat4 m_ScaleMat;

	bool m_enabled;
	const char* m_tag;

public:
	Entity(Renderer* renderer);
	~Entity();		
	virtual void Update(float deltaTime) = 0;

	bool GetIsEnabled() const { return m_enabled; }
	void SetIsEnabled(bool isEnabled) { m_enabled = isEnabled; }

	void Translate(float x, float y, float z);
	void Translate(const glm::vec3& translate);
	void SetPos(float x, float y, float z);
	void SetScale(float x, float y, float z);

	// Rotate entity based on local axis orientation
	void SetRotation(float x, float y, float z);
	void SetRotation(glm::vec3 axis, float angle);

	void SetRotX(float angle);
	void SetRotY(float angle);
	void SetRotZ(float angle);
	glm::vec3 GetPos() { return m_Position; }
	glm::vec3 GetScale() { return m_Scale; }
	glm::vec3 GetRotation() { return m_Rotation; }
	
	void RecalculateUnitVectors();
	void UpdateModelMatrix();

	BoxCollider* GetBoxCollider() { return m_collider; }
	const char* GetTag() { return m_tag; }
};


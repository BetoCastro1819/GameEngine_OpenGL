#pragma once
#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class ENGINEDLL_API Entity {
protected:
	Renderer* m_renderer;
	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec3 m_Rotation;

	glm::mat4 _modelMatrix;
	
	glm::mat4 _translateMatrix;
	glm::mat4 _rotateMatrix;
	glm::mat4 _scaleMatrix;


public:
	Entity(Renderer* renderer);
	~Entity();		
	virtual void Draw() = 0;
	void SetPos(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRotX(float angle);
	void SetRotY(float angle);
	void SetRotZ(float angle);
	glm::vec3 GetPos() { return m_Position; }
	glm::vec3 GetScale() { return m_Scale; }
	glm::vec3 GetRotation() { return m_Rotation; }
	void UpdateModelMatrix();
};


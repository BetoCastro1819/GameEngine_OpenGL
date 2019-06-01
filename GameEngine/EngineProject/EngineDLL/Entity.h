#pragma once
#include "Renderer.h"
#include "SceneNode.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class ENGINEDLL_API Entity : public SceneNode {
protected:
	Renderer* m_renderer;

	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::vec3 m_rotation;

	glm::mat4 m_modelMatrix;
	glm::mat4 m_translateMatrix;
	glm::mat4 m_rotateMatrix;
	glm::mat4 m_scaleMatrix;


public:
	Entity(Renderer* renderer);
	~Entity();		
	virtual void Draw() = 0;
	void SetPos(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRotX(float angle);
	void SetRotY(float angle);
	void SetRotZ(float angle);
	glm::vec3 GetPos() { return m_position; }
	glm::vec3 GetScale() { return m_scale; }
	glm::vec3 GetRotation() { return m_rotation; }
	void UpdateModelMatrix();
};


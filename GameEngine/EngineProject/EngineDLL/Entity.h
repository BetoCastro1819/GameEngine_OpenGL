#pragma once
#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class ENGINEDLL_API Entity {
protected:
	Renderer* _renderer;
	glm::vec3 v3Pos;
	glm::vec3 v3Scale;
	glm::vec3 v3Rot;

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
	glm::vec3 GetPos() { return v3Pos; }
	glm::vec3 GetScale() { return v3Scale; }
	glm::vec3 GetRotation() { return v3Rot; }
	void UpdateModelMatrix();
};


#include "Entity.h"

Entity::Entity(Renderer* renderer)	 {
	_renderer = renderer;
	
	_modelMatrix = glm::mat4(1.0f);

	_translateMatrix = glm::mat4(1.0f);
	_rotateMatrix = glm::mat4(1.0f);
	_scaleMatrix = glm::mat4(1.0f);

	v3Pos[0] = v3Pos[1] = v3Pos[2] = 0.0f;
	v3Scale[0] = v3Scale[1] = v3Scale[2] = 1.0f;
	v3Rot[0] = v3Rot[1] = v3Rot[2] = 0.0f;
}

Entity::~Entity() {
}

void Entity::SetPos(float x, float y, float z) {
	v3Pos[0] = x;
	v3Pos[1] = y;
	v3Pos[2] = z;

	_translateMatrix = glm::translate(_translateMatrix, v3Pos);
	UpdateModelMatrix();
}

void Entity::SetScale(float x, float y, float z) {
	v3Scale[0] = x;
	v3Scale[1] = y;
	v3Scale[2] = z;

	_scaleMatrix = glm::scale(_scaleMatrix, v3Scale);
	UpdateModelMatrix();
}

void Entity::SetRotX(float angle) {
	v3Rot[0] = angle;
	v3Rot[1] = 0;
	v3Rot[2] = 0;

	_rotateMatrix = glm::rotate(_rotateMatrix, glm::radians(angle), v3Rot);
	UpdateModelMatrix();
}

void Entity::SetRotY(float angle) {
	v3Rot[0] = 0;
	v3Rot[1] = angle;
	v3Rot[2] = 0;

	_rotateMatrix = glm::rotate(_rotateMatrix, glm::radians(angle), v3Rot);
	UpdateModelMatrix();
}

void Entity::SetRotZ(float angle) {
	v3Rot[0] = 0;
	v3Rot[1] = 0;
	v3Rot[2] = angle;

	_rotateMatrix = glm::rotate(_rotateMatrix, glm::radians(angle), v3Rot);
	UpdateModelMatrix();
}

void Entity::UpdateModelMatrix() {
	// Matrix multiplications read from right to left, order matters
	_modelMatrix = _translateMatrix * _rotateMatrix * _scaleMatrix;
}
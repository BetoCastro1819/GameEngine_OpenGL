#include "Transform.h"

Transform::Transform() {
	m_modelMatrix = glm::mat4(1.0f);

	m_translateMatrix = glm::mat4(1.0f);
	m_rotateMatrix = glm::mat4(1.0f);
	m_scaleMatrix = glm::mat4(1.0f);

	m_position[0] = m_position[1] = m_position[2] = 0.0f;
	m_scale[0] = m_scale[1] = m_scale[2] = 1.0f;
	m_rotation[0] = m_rotation[1] = m_rotation[2] = 0.0f;
}

void Transform::SetPosition(const glm::vec3& position) {
	m_position = position;
	m_translateMatrix = glm::translate(glm::mat4(1.0f), m_position);
}

void Transform::SetPosition(float x, float y, float z) {
	m_position = glm::vec3(x, y, z);
	m_translateMatrix = glm::translate(glm::mat4(1.0f), m_position);
}

void Transform::SetScale(const glm::vec3& scale) { 
	m_scale = scale;
	m_scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);
}

void Transform::SetScale(float x, float y, float z) {
	m_scale = glm::vec3(x, y, z);
	m_scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);
}

void Transform::SetRotX(float angle) {
	m_rotation[0] = angle;
	m_rotation[1] = 0;
	m_rotation[2] = 0;
	
	m_rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_rotation);
}

void Transform::SetRotY(float angle) {
	m_rotation[0] = 0;
	m_rotation[1] = angle;
	m_rotation[2] = 0;

	m_rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_rotation);
}

void Transform::SetRotZ(float angle) {
	m_rotation[0] = 0;
	m_rotation[1] = 0;
	m_rotation[2] = angle;

	m_rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_rotation);
}

void Transform::UpdateModelMatrix() {
	m_modelMatrix = m_translateMatrix * m_rotateMatrix * m_scaleMatrix;

	//if (m_parent != nullptr)
	//	m_modelMatrix = m_parent->GetMatrix() * m_modelMatrix;
	//
	//UpdateChildrenTransform();
}

void Transform::SetModelMatrix(const glm::mat4& modelMatrix) {
	m_modelMatrix = modelMatrix;
}


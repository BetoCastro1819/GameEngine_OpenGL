#include "Transform.h"
#include "Entity.h"

glm::vec3 World::up = glm::vec3(0, 1, 0);
glm::vec3 World::right = glm::vec3(1, 0, 0);
glm::vec3 World::foward = glm::vec3(0, 0, 1);

Transform::Transform(Entity* entity) : Component(entity) {
	SetType(ComponentType::TRANSFORM);

	m_modelMatrix = glm::mat4(1.0f);

	m_translateMatrix = glm::mat4(1.0f);
	m_rotateMatrix = glm::mat4(1.0f);
	m_scaleMatrix = glm::mat4(1.0f);

	m_position = glm::vec3(0.0f);
	m_scale = glm::vec3(1.0f);
	m_rotation = glm::vec3(0.0f);

	right = World::right;
	foward = World::foward;
	up = World::up;
}

void Transform::Update(float deltaTime) {
	UpdateModelMatrix();
}

void Transform::UpdateModelMatrix() {
	m_modelMatrix = m_translateMatrix * m_rotateMatrix * m_scaleMatrix;

	if (m_entity->GetParent() != nullptr) {
		Transform* parentTransform = m_entity->GetParent()->GetTransform();
		m_modelMatrix = parentTransform->GetModelMatrix() * m_modelMatrix;
	}
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

void Transform::Walk(float speed) {
	m_position += foward * speed;
}

void Transform::Strafe(float speed) {
	m_position += right * speed;
}

void Transform::Pitch(float angle) {
	m_rotation.x = angle;
	m_rotateMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), World::right);
	UpdateUnitVectors();
}

void Transform::Yaw(float angle) {
	m_rotation.y = angle;
	m_rotateMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), World::up);
	UpdateUnitVectors();
}

void Transform::Roll(float angle) {
	m_rotation.z = angle;
	m_rotateMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), World::foward);
	UpdateUnitVectors();
}

void Transform::UpdateUnitVectors() {
	glm::vec4 newFoward = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	newFoward = m_rotateMatrix * newFoward;
	foward.x = newFoward.x;
	foward.y = newFoward.y;
	foward.z = newFoward.z;

	glm::vec4 newUp = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	newUp = m_rotateMatrix * newUp;
	up.x = newUp.x;
	up.y = newUp.y;
	up.z = newUp.z;

	right = glm::normalize(glm::cross(foward, up));
}

//void Transform::SetRotX(float angle) {
//	m_rotation[0] = angle;
//	m_rotation[1] = 0;
//	m_rotation[2] = 0;
//	
//	m_rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_rotation);
//}
//
//void Transform::SetRotY(float angle) {
//	m_rotation[0] = 0;
//	m_rotation[1] = angle;
//	m_rotation[2] = 0;
//
//	m_rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_rotation);
//}
//
//void Transform::SetRotZ(float angle) {
//	m_rotation[0] = 0;
//	m_rotation[1] = 0;
//	m_rotation[2] = angle;
//
//	m_rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_rotation);
//}
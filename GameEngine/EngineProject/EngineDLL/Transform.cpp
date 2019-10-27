#include "Transform.h"
#include "Entity.h"

glm::vec3 World::up = glm::vec3(0, 1, 0);
glm::vec3 World::right = glm::vec3(1, 0, 0);
glm::vec3 World::foward = glm::vec3(0, 0, 1);

Transform::Transform(Entity* entity) : Component(entity) {
	SetType(ComponentType::TRANSFORM);

	m_transform = glm::mat4(1.0f);
	m_worldTransform = glm::mat4(1.0f);

	m_translateMatrix = glm::mat4(1.0f);
	m_rotateMatrix = glm::mat4(1.0f);
	m_scaleMatrix = glm::mat4(1.0f);

	m_position = glm::vec3(0.0f);
	m_scale = glm::vec3(1.0f);
	m_rotation = glm::vec3(0.0f);

	right = World::right;
	foward = World::foward;
	up = World::up;

	m_boundingBox.origin = m_position;
	m_boundingBox.width = glm::vec3(0, 0, 0);
	m_boundingBox.height = glm::vec3(0, 0, 0);
	m_boundingBox.length = glm::vec3(0, 0, 0);

	for (int i = 0; i < 8; i++) {
		m_boundingBox.vertices.push_back(glm::vec3(0));
	}
}

void Transform::Update(float deltaTime) {
	UpdateUnitVectors();
	UpdateModelMatrix();
}

void Transform::UpdateModelMatrix() {
	m_transform = m_translateMatrix * m_rotateMatrix * m_scaleMatrix;

	if (m_entity->GetParent() != nullptr) {
		Transform* parentTransform = m_entity->GetParent()->GetTransform();
		m_worldTransform = parentTransform->GetWorldMatrix() * m_transform;
	} 
	else {
		m_worldTransform = m_transform;
	}


	//for (int i = 0; i < m_boundingBox.vertices.size(); i++) {
	//	glm::vec4 tempVec = glm::vec4(m_boundingBox.vertices[i], 1.0f);
	//	tempVec = m_modelMatrix * tempVec;
	//	m_boundingBox.vertices[i] = glm::vec3(tempVec.x, tempVec.y, tempVec.z);
	//}
}

void Transform::SetPosition(const glm::vec3& position) {
	m_translateMatrix = glm::translate(glm::mat4(1.0f), m_position);

	if (m_entity->GetParent() != nullptr) {
		Transform* parentTransform = m_entity->GetParent()->GetTransform();
		m_position = parentTransform->GetWorldMatrix() * m_translateMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		m_position = m_translateMatrix * m_worldTransform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
}

void Transform::SetPosition(float x, float y, float z) {
	m_translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

	if (m_entity->GetParent() != nullptr) {
		Transform* parentTransform = m_entity->GetParent()->GetTransform();
		m_position = parentTransform->GetWorldMatrix() * m_translateMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		m_position = m_translateMatrix * m_worldTransform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	float posX = m_position.x;
	float posY = m_position.y;
	float posZ = m_position.z;
	printf("\nWorld position: X = %f Y = %f Z = %f \n", posX, posY, posZ);
}

void Transform::SetScale(const glm::vec3& scale) { 
	m_scale = scale;
	m_scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);

	//m_scale = m_scaleMatrix * glm::vec4(m_scale, 1.0f);

	if (m_entity->GetParent() != nullptr) {
		Transform* parentTransform = m_entity->GetParent()->GetTransform();
		m_scale = parentTransform->GetWorldMatrix() * m_scaleMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		m_scale = m_scaleMatrix * m_worldTransform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
}

void Transform::SetScale(float x, float y, float z) {
	m_scale = glm::vec3(x, y, z);
	m_scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);

	//m_scale = m_scaleMatrix * glm::vec4(m_scale, 1.0f);

	if (m_entity->GetParent() != nullptr) {
		Transform* parentTransform = m_entity->GetParent()->GetTransform();
		m_scale = parentTransform->GetWorldMatrix() * m_scaleMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		m_scale = m_scaleMatrix * m_worldTransform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
}

void Transform::Walk(float speed) {
	m_position += foward * speed;
	m_translateMatrix = glm::translate(glm::mat4(1.0f), m_position);

	if (m_entity->GetParent() != nullptr) {
		Transform* parentTransform = m_entity->GetParent()->GetTransform();
		m_position = parentTransform->GetWorldMatrix() * m_translateMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		m_position = m_translateMatrix * m_worldTransform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	//m_position = m_translateMatrix * glm::vec4(m_position, 1.0f);
}

void Transform::Strafe(float speed) {
	m_position += right * speed;
	m_translateMatrix = glm::translate(glm::mat4(1.0f), m_position);

	if (m_entity->GetParent() != nullptr) {
		Transform* parentTransform = m_entity->GetParent()->GetTransform();
		m_position = parentTransform->GetWorldMatrix() * m_translateMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		m_position = m_translateMatrix * m_worldTransform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	//m_position = m_translateMatrix * glm::vec4(m_position, 1.0f);
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

	m_rotation = m_rotateMatrix * glm::vec4(m_rotation, 1.0f);
	if (m_entity->GetParent() != nullptr) {
		Transform* parentTransform = m_entity->GetParent()->GetTransform();
		m_rotation = parentTransform->GetWorldMatrix() * m_rotateMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		m_rotation = m_rotateMatrix * m_worldTransform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
}

void Transform::SetBoundingBoxDimensions(glm::vec3 origin, float width, float height, float length) {
	m_boundingBox.origin = origin;
	m_boundingBox.width = glm::vec3(width, 0, 0);
	m_boundingBox.height = glm::vec3(0, height, 0);
	m_boundingBox.length = glm::vec3(0, 0, length);

	UpdateBoundingBoxVertices();
}


void Transform::SetBoundingBoxDimensions(glm::vec3 minVertex, glm::vec3 maxVertex) {
	m_boundingBox.origin = minVertex;
	m_boundingBox.width = glm::vec3(maxVertex.x, 0, 0);
	m_boundingBox.height = glm::vec3(0, maxVertex.y, 0);
	m_boundingBox.length = glm::vec3(0, 0, maxVertex.z);
	
	UpdateBoundingBoxVertices();
}

void Transform::UpdateBoundingBoxVertices() {
	//glm::vec3 point_frontLowerLeft = origin;
	//glm::vec3 point_frontLowerRight = origin + width;
	//glm::vec3 point_frontUpperRight = origin + width + height;
	//glm::vec3 point_frontUpperLeft = origin + height;
	//
	//glm::vec3 point_backLowerLeft = origin + length;
	//glm::vec3 point_backLowerRight = origin + width + length;
	//glm::vec3 point_backUpperRight = origin + width + height + length;
	//glm::vec3 point_backUpperLeft = origin + height + length;

	// FRONT face vertices
	m_boundingBox.vertices[0] = m_boundingBox.origin;
	m_boundingBox.vertices[1] = m_boundingBox.origin + m_boundingBox.width;
	m_boundingBox.vertices[2] = m_boundingBox.origin + m_boundingBox.width + m_boundingBox.height;
	m_boundingBox.vertices[3] = m_boundingBox.origin + m_boundingBox.height;

	// BACK face vertices
	m_boundingBox.vertices[4] = m_boundingBox.origin + m_boundingBox.length;
	m_boundingBox.vertices[5] = m_boundingBox.origin + m_boundingBox.width + m_boundingBox.length;
	m_boundingBox.vertices[6] = m_boundingBox.origin + m_boundingBox.width + m_boundingBox.length + m_boundingBox.height;
	m_boundingBox.vertices[7] = m_boundingBox.origin + m_boundingBox.height + m_boundingBox.length;
}
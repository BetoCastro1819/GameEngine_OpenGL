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

	m_boundingBox.minVertex = glm::vec3(0.0f);
	m_boundingBox.maxVertex = glm::vec3(0.0f);
	
	//m_boundingBox.width = glm::vec3(0, 0, 0);
	//m_boundingBox.height = glm::vec3(0, 0, 0);
	//m_boundingBox.length = glm::vec3(0, 0, 0);

	for (int i = 0; i < 8; i++) {
		m_boundingBox.vertices.push_back(glm::vec3(0));
	}
}

void Transform::Update(float deltaTime) {
	UpdateUnitVectors();
	UpdateModelMatrix();
	UpdateBoundingBoxVertices();

	//printf("\nX: %f Y: %f Z: %f", m_position.x, m_position.y, m_position.z);
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
}

void Transform::SetPosition(const glm::vec3& position) {
	m_translateMatrix = glm::translate(glm::mat4(1.0f), position);
	UpdateVectorWithMatrix(m_position, m_translateMatrix);
}

void Transform::SetPosition(float x, float y, float z) {
	m_translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	UpdateVectorWithMatrix(m_position, m_translateMatrix);

	glm::vec3 worldPos = glm::vec4(m_position, 1.0f) * m_worldTransform;

	printf("\n%s is at X: %f Y: %f Z: %f\n",
		m_entity->GetName(),
		worldPos.x,
		worldPos.y,
		worldPos.z
	);
}

void Transform::SetScale(const glm::vec3& scale) { 
	m_scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
	UpdateVectorWithMatrix(m_scale, m_scaleMatrix);
}

void Transform::SetScale(float x, float y, float z) {
	m_scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
	UpdateVectorWithMatrix(m_scale, m_scaleMatrix);
}

void Transform::Walk(float speed) {
	m_position += foward * speed;
	m_translateMatrix = glm::translate(glm::mat4(1.0f), m_position);
	UpdateVectorWithMatrix(m_position, m_translateMatrix);
}

void Transform::Strafe(float speed) {
	m_position += right * speed;
	m_translateMatrix = glm::translate(glm::mat4(1.0f), m_position);
	UpdateVectorWithMatrix(m_position, m_translateMatrix);
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

	UpdateVectorWithMatrix(m_rotation, m_rotateMatrix);
}


void Transform::UpdateVectorWithMatrix(glm::vec3& vectorToUpdate, glm::mat4 matToUse) {
	
	if (m_entity->GetParent() != nullptr) {
		Transform* parentTransform = m_entity->GetParent()->GetTransform();
		vectorToUpdate = parentTransform->GetWorldMatrix() * matToUse *  glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		vectorToUpdate = m_worldTransform * matToUse * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	UpdateModelMatrix();
}

void Transform::SetBoundingBoxDimensions(glm::vec3 origin, float width, float height, float length) {
	//m_boundingBox.origin = origin;
	//m_boundingBox.width = glm::vec3(width, 0, 0);
	//m_boundingBox.height = glm::vec3(0, height, 0);
	//m_boundingBox.length = glm::vec3(0, 0, length);
	//
	//UpdateBoundingBoxVertices();
}


void Transform::SetBoundingBoxDimensions(glm::vec3 minVertex, glm::vec3 maxVertex) {
	m_boundingBox.minVertex = minVertex;
	m_boundingBox.maxVertex = maxVertex;
	
	UpdateBoundingBoxVertices();
}

void Transform::UpdateBoundingBoxVertices() {
	UpdateBBoxBasedOnChildBounds();

	// BACK face vertices
	m_boundingBox.vertices[0] = m_position + m_boundingBox.minVertex;
	m_boundingBox.vertices[1] = m_position + glm::vec3(m_boundingBox.minVertex.x, m_boundingBox.maxVertex.y, m_boundingBox.minVertex.z);
	m_boundingBox.vertices[2] = m_position + glm::vec3(m_boundingBox.maxVertex.x, m_boundingBox.maxVertex.y, m_boundingBox.minVertex.z); 
	m_boundingBox.vertices[3] = m_position + glm::vec3(m_boundingBox.maxVertex.x, m_boundingBox.minVertex.y, m_boundingBox.minVertex.z); 

	// FRONT face vertices		
	m_boundingBox.vertices[4] = m_position + glm::vec3(m_boundingBox.minVertex.x, m_boundingBox.minVertex.y, m_boundingBox.maxVertex.z);
	m_boundingBox.vertices[5] = m_position + glm::vec3(m_boundingBox.minVertex.x, m_boundingBox.maxVertex.y, m_boundingBox.maxVertex.z);
	m_boundingBox.vertices[6] = m_position + m_boundingBox.maxVertex;
	m_boundingBox.vertices[7] = m_position + glm::vec3(m_boundingBox.maxVertex.x, m_boundingBox.minVertex.y, m_boundingBox.maxVertex.z);

	// TODO: multiply by each vertex by worldTransform
	//m_boundingBox.vertices[0] = m_worldTransform * glm::vec4(m_boundingBox.vertices[0], 1.0f);
	//m_boundingBox.vertices[1] = m_worldTransform * glm::vec4(m_boundingBox.vertices[1], 1.0f);
	//m_boundingBox.vertices[2] = m_worldTransform * glm::vec4(m_boundingBox.vertices[2], 1.0f);
	//m_boundingBox.vertices[3] = m_worldTransform * glm::vec4(m_boundingBox.vertices[3], 1.0f);
	//
	//// FRONT face vertices		
	//m_boundingBox.vertices[4] = m_worldTransform * glm::vec4(m_boundingBox.vertices[4], 1.0f);
	//m_boundingBox.vertices[5] = m_worldTransform * glm::vec4(m_boundingBox.vertices[5], 1.0f);
	//m_boundingBox.vertices[6] = m_worldTransform * glm::vec4(m_boundingBox.vertices[6], 1.0f);
	//m_boundingBox.vertices[7] = m_worldTransform * glm::vec4(m_boundingBox.vertices[7], 1.0f);
}

void Transform::UpdateBBoxBasedOnChildBounds() {
	CompareCurrentBBoxAgainstChilds(m_boundingBox.minVertex, m_boundingBox.maxVertex);
}

void Transform::CompareCurrentBBoxAgainstChilds(glm::vec3& currentMinVertex, glm::vec3& currentMaxVertex) {
	for (int childIndex = 0; childIndex < m_entity->GetChildren().size(); childIndex++) {

		Entity* child = (Entity*)m_entity->GetChildren()[childIndex];
		
		BoundingBox childBBox = child->GetTransform()->GetBoundingBox();
		for (int vertexId = 0; vertexId < childBBox.vertices.size(); vertexId++) {

			glm::vec3 currentVertex = childBBox.vertices[vertexId];
			if (currentVertex.x < currentMinVertex.x) {
				currentMinVertex.x = currentVertex.x;
			}
			if (currentVertex.y < currentMinVertex.y) {
				currentMinVertex.y = currentVertex.y;
			}
			if (currentVertex.z < currentMinVertex.z) {
				currentMinVertex.z = currentVertex.z;
			}
			if (currentVertex.x > currentMaxVertex.x) {
				currentMaxVertex.x = currentVertex.x;
			}
			if (currentVertex.y > currentMaxVertex.y) {
				currentMaxVertex.y = currentVertex.y;
			}
			if (currentVertex.z > currentMaxVertex.z) {
				currentMaxVertex.z = currentVertex.z;
			}
		}
		child->GetTransform()->CompareCurrentBBoxAgainstChilds(currentMinVertex, currentMaxVertex);
	}
}
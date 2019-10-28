#pragma once
#include "Exports.h"
#include "Component.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

struct World {
	static glm::vec3 up;
	static glm::vec3 right;
	static glm::vec3 foward;
};

struct BoundingBox {
	glm::vec3 minVertex;
	glm::vec3 maxVertex;
	//glm::vec3 width;
	//glm::vec3 height;
	//glm::vec3 length;
	std::vector<glm::vec3> vertices;
};

class ENGINEDLL_API Transform  : public Component {
private:
	BoundingBox m_boundingBox;

	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::vec3 m_rotation;

	glm::mat4 m_worldTransform;
	glm::mat4 m_transform;

	glm::mat4 m_translateMatrix;
	glm::mat4 m_rotateMatrix;
	glm::mat4 m_scaleMatrix;

	void UpdateUnitVectors();
	void UpdateBoundingBoxVertices();
	void UpdateVectorWithMatrix(glm::vec3& vectorToUpdate, glm::mat4 matToUse);

public:
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 foward;

	Transform(Entity* entity);
	~Transform() { }

	void Update(float deltaTime) override;

	glm::mat4 GetWorldMatrix() const { return m_worldTransform; }
	void UpdateModelMatrix();

	glm::vec3 GetPosition() const { return m_position; }
	glm::vec3 GetScale() const { return m_scale; }
	glm::vec3 GetRotation() const { return m_rotation; }

	void SetPosition(const glm::vec3& position);
	void SetPosition(float x, float y, float z);
	void SetScale(const glm::vec3& scale);
	void SetScale(float x, float y, float z);

	void Walk(float speed);
	void Strafe(float speed);
	void Pitch(float angle);
	void Yaw(float angle);
	void Roll(float angle);

	void SetBoundingBoxDimensions(glm::vec3 origin, float width, float height, float length);
	void SetBoundingBoxDimensions(glm::vec3 minVertex, glm::vec3 maxVertex);
	BoundingBox GetboundingBox() { return m_boundingBox; }
};


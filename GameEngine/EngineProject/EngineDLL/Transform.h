#pragma once
#include "Exports.h"
#include "Component.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class ENGINEDLL_API Transform  : public Component {
private:
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::vec3 m_rotation;

	glm::mat4 m_modelMatrix;
	glm::mat4 m_translateMatrix;
	glm::mat4 m_rotateMatrix;
	glm::mat4 m_scaleMatrix;

public:
	Transform(Entity* entity);
	~Transform() { }

	void Update(float deltaTime) override;

	glm::mat4 GetModelMatrix() const { return m_modelMatrix; }
	glm::mat4 GetMatrix() { return m_modelMatrix; }
	void UpdateModelMatrix();
	//void UpdateLocalTransform(const glm::mat4& parentMatrix);

	glm::vec3 GetPosition() const { return m_position; }
	glm::vec3 GetScale() const { return m_scale; }
	glm::vec3 GetRotation() const { return m_rotation; }

	void SetPosition(const glm::vec3& position);
	void SetPosition(float x, float y, float z);
	void SetScale(const glm::vec3& scale);
	void SetScale(float x, float y, float z);

	void SetRotX(float angle);
	void SetRotY(float angle);
	void SetRotZ(float angle);
};


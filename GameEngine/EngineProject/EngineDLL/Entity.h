#pragma once
#include "Renderer.h"
#include "SceneNode.h"

class ENGINEDLL_API Entity : public SceneNode {
protected:
	Renderer* m_renderer;

public:
	Entity(Renderer* renderer);
	~Entity();

	void Update(float deltaTime) override;

	//void UpdateLocalTransform(const glm::mat4& parentMatrix);
	//glm::mat4 GetMatrix() { return m_transform->GetModelMatrix(); }
	//void UpdateModelMatrix();
	//void UpdateChildrenTransform();

	//void SetPos(float x, float y, float z);
	//void SetScale(float x, float y, float z);
	//void SetRotX(float angle);
	//void SetRotY(float angle);
	//void SetRotZ(float angle);
	//glm::vec3 GetPos() { return m_transform->GetPosition(); }
	//glm::vec3 GetScale() { return m_transform->GetScale(); }
	//glm::vec3 GetRotation() { return m_transform->GetRotation(); }
};

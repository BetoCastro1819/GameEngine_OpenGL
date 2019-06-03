#pragma once
#include "Exports.h"
#include "Transform.h"
#include <list>

class ENGINEDLL_API SceneNode {
private:
	void SetParent(SceneNode* parent);

protected:
	Transform m_transform;
	std::list<SceneNode*> m_childrenList;
	SceneNode* m_parent;

public:
	SceneNode() : m_parent(nullptr) { }
	virtual ~SceneNode();
	void Release();

	virtual void Update(float deltaTime);
	void Destroy();
	void AddChild(SceneNode* child);
	void UpdateLocalTransform(const glm::mat4& parentMatrix);
	glm::mat4 GetMatrix() { return m_transform.GetModelMatrix(); }
	void UpdateModelMatrix();
	void UpdateChildrenTransform();
};


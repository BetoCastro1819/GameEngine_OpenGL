#pragma once
#include "Exports.h"
#include <list>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class ENGINEDLL_API SceneNode {
private:
	void SetParent(SceneNode* parent);

protected:
	std::list<SceneNode*> m_childrenList;
	SceneNode* m_parent;

	glm::mat4 m_modelMatrix;
	glm::mat4 m_translateMatrix;
	glm::mat4 m_rotateMatrix;
	glm::mat4 m_scaleMatrix;

public:
	SceneNode() : m_parent(nullptr) { }
	virtual ~SceneNode();
	void Release();

	virtual void Update();
	void DestroyAllChildren();
	void AddChild(SceneNode* child);
	void UpdateLocalTransform(const glm::mat4& parentMatrix);
	glm::mat4 GetMatrix() { return m_modelMatrix; }
	void UpdateModelMatrix();
	void UpdateChildrenTransform();
};


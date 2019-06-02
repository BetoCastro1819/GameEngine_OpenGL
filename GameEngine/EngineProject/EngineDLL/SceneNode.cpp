#include "SceneNode.h"

void SceneNode::SetParent(SceneNode* parent) {
	m_parent = parent;
}

void SceneNode::AddChild(SceneNode* child) {
	if (child != nullptr) {
		m_childrenList.push_back(child);
		child->SetParent(this);
	}
}

void SceneNode::Update() {
	for (std::list<SceneNode*>::iterator iter = m_childrenList.begin();
		iter != m_childrenList.end(); iter++) {
		(*iter)->Update();
	}
}

void SceneNode::UpdateModelMatrix() {
	m_modelMatrix = m_translateMatrix * m_rotateMatrix * m_scaleMatrix;

	if (m_parent != nullptr)
		m_modelMatrix = m_parent->GetMatrix() * m_modelMatrix;

	UpdateChildrenTransform();
}

void SceneNode::UpdateChildrenTransform() {
	for (std::list<SceneNode*>::iterator iter = m_childrenList.begin();
		iter != m_childrenList.end(); iter++)
	{
		(*iter)->UpdateLocalTransform(m_modelMatrix);
		(*iter)->UpdateModelMatrix();
	}
}

void SceneNode::UpdateLocalTransform(const glm::mat4& parentMatrix) {
	m_modelMatrix = parentMatrix * m_modelMatrix;
}

void SceneNode::Release() {
	delete this;
}

SceneNode::~SceneNode() {
	DestroyAllChildren();
}

void SceneNode::DestroyAllChildren() {
	for (std::list<SceneNode*>::iterator iter = m_childrenList.begin();
		iter != m_childrenList.end(); iter++) {
		(*iter)->Release();
	}
	m_childrenList.clear();
}

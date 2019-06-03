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

void SceneNode::Update(float deltaTime) {
	for (std::list<SceneNode*>::iterator iter = m_childrenList.begin();
		iter != m_childrenList.end(); iter++) {
		(*iter)->Update(deltaTime);
	}
}

void SceneNode::UpdateModelMatrix() {
	m_transform.UpdateModelMatrix();

	if (m_parent != nullptr)
		m_transform.SetModelMatrix(m_parent->GetMatrix() * m_transform.GetModelMatrix());

	UpdateChildrenTransform();
}

void SceneNode::UpdateChildrenTransform() {
	std::list<SceneNode*>::iterator iter;
	for (iter = m_childrenList.begin();	iter != m_childrenList.end(); iter++) {
		(*iter)->UpdateLocalTransform(m_transform.GetModelMatrix());
		(*iter)->UpdateModelMatrix();
	}
}

void SceneNode::UpdateLocalTransform(const glm::mat4& parentMatrix) {
	m_transform.SetModelMatrix(parentMatrix * m_transform.GetModelMatrix());
}

void SceneNode::Release() {
	delete this;
}

SceneNode::~SceneNode() {
	Destroy();
}

void SceneNode::Destroy() {
	for (std::list<SceneNode*>::iterator iter = m_childrenList.begin();
		iter != m_childrenList.end(); iter++) {
		(*iter)->Release();
	}
	m_childrenList.clear();
}

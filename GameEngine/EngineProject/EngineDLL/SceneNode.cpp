#include "SceneNode.h"
#include "Transform.h"

void SceneNode::SetParent(SceneNode* parent) {
	m_parent = parent;
}

void SceneNode::AddNode(SceneNode* node) {
	if (node != nullptr) {
		m_nodeList.push_back(node);
		node->SetParent(this);
	}
}

void SceneNode::Update(float deltaTime) {
	for (std::list<SceneNode*>::iterator iter = m_nodeList.begin();
		iter != m_nodeList.end(); iter++) {
		(*iter)->Update(deltaTime);
	}
}

Component* SceneNode::GetComponent(ComponentType componentType) {
	for (std::list<Component*>::iterator iter = m_componentList.begin();
		iter != m_componentList.end(); iter++) {
		if ((*iter)->GetType() == componentType)
			return *iter;
	}
	return nullptr;
}

SceneNode::~SceneNode() {
	Destroy();
}

void SceneNode::Destroy() {
	for (std::list<SceneNode*>::iterator iter = m_nodeList.begin();
		iter != m_nodeList.end(); iter++) {
		(*iter)->Release();
	}
	m_nodeList.clear();
}

void SceneNode::Release() {
	delete this;
}

SceneNode* SceneNode::GetParent() { return m_parent; }
Transform* SceneNode::GetTransform() { return m_transform; }

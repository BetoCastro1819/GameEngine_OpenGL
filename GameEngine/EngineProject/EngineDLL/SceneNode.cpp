#include "SceneNode.h"
#include "Transform.h"

void SceneNode::SetParent(SceneNode* parent) {
	m_parent = parent;
}

void SceneNode::AddNode(SceneNode* node) {
	if (node != nullptr) {
		m_children.push_back(node);
		node->SetParent(this);
	}
}

void SceneNode::Update(float deltaTime) {
	for (std::vector<Component*>::iterator iter = m_componentList.begin();
		iter != m_componentList.end(); iter++) {
		(*iter)->Update(deltaTime);
	}

	for (std::vector<SceneNode*>::iterator iter = m_children.begin();
		iter != m_children.end(); iter++) {
		(*iter)->Update(deltaTime);
	}
}

Component* SceneNode::GetComponent(ComponentType componentType) {
	for (std::vector<Component*>::iterator iter = m_componentList.begin();
		iter != m_componentList.end(); iter++) {
		if ((*iter)->GetType() == componentType)
			return *iter;
	}
	return nullptr;
}

void SceneNode::PrintNodeHierarchy() {
	for (int i = 0; i < m_children.size(); i++) {
		//printf("\nsome word\n");
	}
}

SceneNode::~SceneNode() {
	Destroy();
}

void SceneNode::Destroy() {
	for (std::vector<SceneNode*>::iterator iter = m_children.begin();
		iter != m_children.end(); iter++) {
		if ((*iter) != nullptr)
			(*iter)->Release();
	}
	m_children.clear();
}

void SceneNode::Release() {
	delete this;
}

SceneNode* SceneNode::GetParent() {
	return m_parent;
}

Transform* SceneNode::GetTransform() {
	return m_transform;
}

SceneNode* SceneNode::GetChildrenByIndex(int index) {
	if (index >= 0 && index < m_children.size())
		return m_children[index];
	printf("\nERROR from %s: SELECTED CHILDREN INDEX IS OUT OF RANGE!!!\n", m_name);
	return this;
}

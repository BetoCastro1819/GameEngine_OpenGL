#include "SceneNode.h"
#include "Transform.h"

SceneNode::SceneNode() {
	m_parent = nullptr;
	m_transform = nullptr;
	m_name = "name undefined";
}

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


void SceneNode::PrintNodeHierarchy() {
	int treeLevel = 0;
	printf("\nRoot node\n");
	TraverseNodeTree(treeLevel);
}

void SceneNode::TraverseNodeTree(int& treeLevel) {
	for (int i = m_children.size() - 1; i >= 0 ; i--) {
		for (int j = 0; j <= treeLevel; j++) {
			printf(" |-");
		}
		printf("%s\n", m_children[i]->GetName());
		m_children[i]->TraverseNodeTree(++treeLevel);
		treeLevel--;
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
	printf("\nERROR from %s: SELECTED CHILDREN INDEX IS OUT OF RANGE!!!\n", GetName());
	return this;
}

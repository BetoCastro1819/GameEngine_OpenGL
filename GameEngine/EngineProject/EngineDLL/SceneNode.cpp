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

		printf("\n%s is child of %s\n", node->GetName(), this->GetName());
		printf("\n%s has %d childs\n", this->GetName(), m_children.size());
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
	printf("\nRoot node: %s\n", GetName());
	TraverseNodeTree(treeLevel);
}

void SceneNode::TraverseNodeTree(int& treeLevel) {
	for (int i = 0; i < m_children.size() ; i++) {
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

Transform* SceneNode::GetTransform() const {
	return m_transform;
}

SceneNode* SceneNode::GetChildrenByIndex(int index) {
	if (index >= 0 && index < m_children.size())
		return m_children[index];
	printf("\nERROR from %s: SELECTED CHILDREN INDEX IS OUT OF RANGE!!!\n", GetName());
	return this;
}

void SceneNode::GetAllChildren(std::vector<SceneNode*>& children) {
	for (int i = 0; i < m_children.size(); i++) {
		m_children[i]->GetAllChildren(children);
		children.push_back(m_children[i]);
	}
}


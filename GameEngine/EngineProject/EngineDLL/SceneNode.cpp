#include "SceneNode.h"

void SceneNode::AddChild(SceneNode* child) {
	m_childrenList.push_back(child);
}

void SceneNode::Update() {
	for (std::list<SceneNode*>::iterator iter = m_childrenList.begin();
		iter != m_childrenList.end(); iter++) {
		(*iter)->Update();
	}
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

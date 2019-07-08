#pragma once
#include "Exports.h"
#include "Component.h"
#include <vector>

class Transform;
enum ComponentType;

class ENGINEDLL_API SceneNode {
private:
	void SetParent(SceneNode* parent);

protected:
	Transform* m_transform;
	SceneNode* m_parent;

	std::vector<SceneNode*> m_children;
	std::vector<Component*> m_componentList;

public:
	SceneNode() : m_parent(nullptr), m_transform(nullptr) {	}

	virtual ~SceneNode();
	void Release();

	virtual void Update(float deltaTime);
	void Destroy();
	void AddNode(SceneNode* node);

	void AddComponent(Component* component) { m_componentList.push_back(component); }
	Component* GetComponent(ComponentType componentType);

	SceneNode* GetParent();
	Transform* GetTransform();
	SceneNode* GetChildrenByIndex(int index); 
};


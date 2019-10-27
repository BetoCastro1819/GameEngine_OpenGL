#pragma once
#include "Exports.h"
#include "Component.h"
#include <vector>
#include <String>

class Transform;
enum ComponentType;

class ENGINEDLL_API SceneNode {
private:
	std::string m_name;

	void TraverseNodeTree(int& treeLevel);
	void SetParent(SceneNode* parent);

protected:
	Transform* m_transform;
	SceneNode* m_parent;

	std::vector<SceneNode*> m_children;
	std::vector<Component*> m_componentList;

public:
	SceneNode();

	virtual ~SceneNode();
	void Release();

	virtual void Update(float deltaTime);
	void Destroy();
	void AddNode(SceneNode* node);
	void PrintNodeHierarchy();

	void AddComponent(Component* component) { m_componentList.push_back(component); }
	Component* GetComponent(ComponentType componentType);

	SceneNode* GetParent();
	Transform* GetTransform();
	SceneNode* GetChildrenByIndex(int index); 

	void SetName(std::string name) { m_name = name; }
	const char* GetName() { return m_name.c_str(); }

	std::vector<SceneNode*> GetChildren() const { return m_children; }
};


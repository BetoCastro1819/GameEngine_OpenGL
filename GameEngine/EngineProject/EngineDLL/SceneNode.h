#pragma once
#include "Exports.h"
#include <list>

class ENGINEDLL_API SceneNode {
protected:
	std::list<SceneNode*> m_childrenList;

public:
	SceneNode() { }
	virtual ~SceneNode();
	void Release();

	virtual void Update();
	void DestroyAllChildren();
	void AddChild(SceneNode* child);
};


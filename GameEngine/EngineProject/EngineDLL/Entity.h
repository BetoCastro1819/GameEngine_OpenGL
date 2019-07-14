#pragma once
#include "Renderer.h"
#include "SceneNode.h"

class ENGINEDLL_API Entity : public SceneNode {
protected:
	Renderer* m_renderer;

public:
	Entity(Renderer* renderer);
	~Entity();

	void Update(float deltaTime) override;


};

#pragma once
#include "Renderer.h"
#include "SceneNode.h"

class ENGINEDLL_API Entity : public SceneNode {
protected:
	Renderer* m_renderer;
	bool m_isVisible;

public:
	Entity(Renderer* renderer);
	~Entity();

	void Update(float deltaTime) override;
	void SetVisible(bool isVisible) { m_isVisible = isVisible; }
	bool isInsideFrustrum() const { return m_isVisible; }
	void DrawBoundingBox();
};

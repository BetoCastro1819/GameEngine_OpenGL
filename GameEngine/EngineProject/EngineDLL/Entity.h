#pragma once
#include "Renderer.h"
#include "SceneNode.h"

class ENGINEDLL_API Entity : public SceneNode {
protected:
	Renderer* m_renderer;
	bool m_isInsideFrustrum;

public:
	Entity(Renderer* renderer);
	~Entity();

	void Update(float deltaTime) override;
	void SetIsInsideFrustrum(bool isInsideFrustrum) { m_isInsideFrustrum = isInsideFrustrum; }
};

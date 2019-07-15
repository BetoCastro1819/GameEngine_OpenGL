#pragma once
#include "Renderer.h"
#include "SceneNode.h"

class ENGINEDLL_API Entity : public SceneNode {
private:
	bool m_isInsideFrustrum;

protected:
	Renderer* m_renderer;

public:
	Entity(Renderer* renderer);
	~Entity();

	void Update(float deltaTime) override;
	void SetIsInsideFrustrum(bool isInsideFrustrum) { m_isInsideFrustrum = isInsideFrustrum; }
};

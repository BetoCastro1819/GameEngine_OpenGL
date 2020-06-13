#pragma once
//#include "Renderer.h"
#include "../../misc/Exports.h"
#include "../SceneNode.h"

class Renderer;

class ENGINEDLL_API Entity : public SceneNode {
protected:
	Renderer* m_renderer;
	bool m_isVisible;

public:
	Entity(Renderer* renderer);
	~Entity();

	virtual void OnContact(float velocityOfImpact) { }

	void Update(float deltaTime) override;
	void SetVisible(bool isVisible) { m_isVisible = isVisible; }
	bool isVisible() const { return m_isVisible; }
	void DrawBoundingBox();
};

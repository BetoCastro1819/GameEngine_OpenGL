#pragma once
#include "Renderer.h"
#include "SceneNode.h"

class ENGINEDLL_API Entity : public SceneNode {
private:
	const char* m_name;

protected:
	Renderer* m_renderer;

public:
	Entity(Renderer* renderer);
	~Entity();

	void Update(float deltaTime) override;

	void SetName(const char* name) { m_name = name; }
	const char* GetName() { return m_name; }
};

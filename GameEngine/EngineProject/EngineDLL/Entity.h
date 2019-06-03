#pragma once
#include "Renderer.h"
#include "SceneNode.h"
#include "Component.h"

class ENGINEDLL_API Entity : public SceneNode {
private:
	list<Component*> m_components;

protected:
	Renderer* m_renderer;

public:
	Entity(Renderer* renderer);
	~Entity();		
	//virtual void Draw() = 0;

	void AddComponent(Component* component) { m_components.push_front(component); }

	void SetPos(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRotX(float angle);
	void SetRotY(float angle);
	void SetRotZ(float angle);
	glm::vec3 GetPos() { return m_transform.GetPosition(); }
	glm::vec3 GetScale() { return m_transform.GetScale(); }
	glm::vec3 GetRotation() { return m_transform.GetRotation(); }
};


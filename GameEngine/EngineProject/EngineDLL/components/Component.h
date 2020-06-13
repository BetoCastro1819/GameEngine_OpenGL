#pragma once
#include "../misc/Exports.h"

class Entity;

enum ComponentType {
	DEFAULT,
	TRANSFORM,
	MESH,
	MATERIAL
};

class ENGINEDLL_API Component {
private:
	ComponentType m_type;

protected:
	Entity* m_entity;
	void SetType(ComponentType type) { m_type = type; }

public:
	Component(Entity* entity);
	~Component();

	virtual void Update(float deltaTime) = 0;
	const ComponentType GetType() { return m_type; }
};


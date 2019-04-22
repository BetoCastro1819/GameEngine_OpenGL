#pragma once

#include "Entity.h"
#include "Material.h"

class ENGINEDLL_API Mesh : public Entity
{
	Renderer* m_Renderer;

public:
	Mesh(Renderer* renderer);
	~Mesh();

	void Draw() override;
};


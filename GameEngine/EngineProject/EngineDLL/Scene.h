#pragma once
#include "Exports.h"
#include "Entity.h"
#include "Renderer.h"

class ENGINEDLL_API Scene : public Entity {
public:
	Scene(Renderer* renderer);
	~Scene();
};


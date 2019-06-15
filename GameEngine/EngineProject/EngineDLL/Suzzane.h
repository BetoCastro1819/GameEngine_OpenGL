#pragma once
#include "Exports.h"
#include "Entity.h"

class ENGINEDLL_API Suzzane : public Entity {
public:
	Suzzane(Renderer* renderer);
	~Suzzane();

	void Update(float deltaTime) override;
};


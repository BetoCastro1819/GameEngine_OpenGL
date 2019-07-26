#pragma once
#include "Sprite.h"
#include "Material.h"
#include "Texture.h"
#include "Entity.h"
#include "CharacterController.h"

class Enemy : public Entity {
public:
	Enemy(Renderer* renderer);
	~Enemy();
};


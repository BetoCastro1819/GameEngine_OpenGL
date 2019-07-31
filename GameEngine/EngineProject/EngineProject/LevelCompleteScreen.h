#pragma once
#include "Sprite.h"
#include "Material.h"
#include "Texture.h"
#include "Entity.h"

class LevelCompleteScreen : public Entity {
private:
	Sprite* m_sprite;
	Texture* m_texture;

	void Update(float deltaTime) override { }

public:
	LevelCompleteScreen(Renderer* renderer, Material* material);
	~LevelCompleteScreen();

	void Display();
};


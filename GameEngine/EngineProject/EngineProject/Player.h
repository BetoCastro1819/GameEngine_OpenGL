#pragma once
#include "Sprite.h"
#include "Material.h"
#include "Texture.h"
#include "Entity.h"

class CharacterController;

class Player : public Entity {
private:
	Sprite* m_sprite;
	Texture* m_texture;
	Window* m_window;
	CharacterController* m_controller;

	void Draw() override;

public:
	Player(Window* window, Renderer* renderer, Material* material);
	~Player();

	void Update(float deltaTime);
};


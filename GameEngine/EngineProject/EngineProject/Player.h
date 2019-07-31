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

	glm::vec3 m_respawnPosition;

	enum State {
		IDLE,
		RUN,
		NOT_GROUNDED
	} m_state;

	void UpdateState(float deltaTime);

public:
	Player(Window* window, Renderer* renderer, Material* material);
	~Player();

	void Update(float deltaTime) override;
	void SetRespawnPosition(const glm::vec3& respawnPos);
	void Respawn();
};


#pragma once
#include "Sprite.h"
#include "Material.h"
#include "Texture.h"
#include "Entity.h"
#include "MovementComponent.h"

class Enemy : public Entity {
private:
	Sprite* m_sprite;
	Texture* m_texture;
	MovementComponent* m_movementComp;

	glm::vec3 m_direction;
	bool m_isGoingLeft;
	bool m_isGrounded;

	void UpdatePosition(float deltaTime);

public:
	Enemy(Renderer* renderer, Material* material);
	~Enemy();

	void Update(float deltaTime) override;
	void Reset();
};


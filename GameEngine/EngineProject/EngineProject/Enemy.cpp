#include "Enemy.h"

Enemy::Enemy(Renderer* renderer, Material* material) : Entity(renderer) {
	m_texture = new Texture("characters.bmp");
	m_texture->SetTextureDimensions(736, 128);
	m_texture->SetFrameDimensions(32, 32);
	m_texture->SetNumberOfFramesPerRow(24);
	m_texture->SetNumberOfFramesPerColumn(4);

	m_sprite = new Sprite(renderer, material, m_texture);
	m_sprite->SetFrameID(73);

	m_collider = new BoxCollider(m_texture->GetFrameWidth(), m_texture->GetFrameHeight());

	m_movementComp = new MovementComponent();
	m_movementComp->SetAcceleration(5.0f);
	m_movementComp->SetDragValue(0.05f);
	m_movementComp->SetMaxSpeed(2);
}

Enemy::~Enemy() {
	if (m_texture != nullptr) delete m_texture;
	if (m_sprite != nullptr) delete m_sprite;
	if (m_collider != nullptr) delete m_collider;
	if (m_movementComp != nullptr) delete m_movementComp;
}

void Enemy::Update(float deltaTime) {
	m_sprite->SetModelMatrix(m_ModelMat);
	m_sprite->Update(deltaTime);
}


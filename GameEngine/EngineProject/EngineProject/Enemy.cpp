#include "Enemy.h"

Enemy::Enemy(Renderer* renderer, Material* material) : Entity(renderer) {

	m_tag = "Enemy";
	
	m_texture = new Texture("characters.bmp");
	m_texture->SetTextureDimensions(736, 128);
	m_texture->SetFrameDimensions(32, 32);
	m_texture->SetNumberOfFramesPerRow(24);
	m_texture->SetNumberOfFramesPerColumn(4);

	m_sprite = new Sprite(renderer, material, m_texture);
	m_sprite->SetFrameID(73);

	m_collider = new BoxCollider(m_texture->GetFrameWidth(), m_texture->GetFrameHeight());

	m_movementComp = new MovementComponent(this);
	m_movementComp->SetMaxSpeed(50);
	m_movementComp->SetDragValue(0.05f);
	m_movementComp->SetAcceleration(5.0f);

	m_direction = -World_Right;
	m_isGoingLeft = true;
	m_isGrounded = false;
}

Enemy::~Enemy() {
	if (m_texture != nullptr) delete m_texture;
	if (m_sprite != nullptr) delete m_sprite;
	if (m_collider != nullptr) delete m_collider;
	if (m_movementComp != nullptr) delete m_movementComp;
}

void Enemy::Update(float deltaTime) {
	if (m_enabled) {
		m_sprite->SetModelMatrix(m_ModelMat);
		m_sprite->Update(deltaTime);
		UpdatePosition(deltaTime);
	}
}

void Enemy::UpdatePosition(float deltaTime) {
	m_movementComp->Update();

	if (GetBoxCollider()->GetCollisionFlag().top) {
		Entity* entity = GetBoxCollider()->GetCollidingEntity();
		if (entity != nullptr && entity->GetTag() == "Player") {
			printf("\nGoompa stomp\n");
			m_enabled = false;
			entity->GetBoxCollider()->SetCollidingEntity(nullptr);
		}
	}
	if (GetBoxCollider()->GetCollisionFlag().bottom) {
		m_isGrounded = true;
	}
	if (m_isGrounded) {
		if (GetBoxCollider()->GetCollisionFlag().left)
			m_isGoingLeft = false;
		else if (GetBoxCollider()->GetCollisionFlag().right)
			m_isGoingLeft = true;

		if (m_isGoingLeft) {
			m_movementComp->SetVelocity(m_direction * 50.0f);
			SetScale(-1.0f, GetScale().y, GetScale().z);
		}
		else {
			m_movementComp->SetVelocity(m_direction * -50.0f);
			SetScale(1.0f, GetScale().y, GetScale().z);
		}
	}

	Translate(m_movementComp->GetVelocity() * deltaTime);
}


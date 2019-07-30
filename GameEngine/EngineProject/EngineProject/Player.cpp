#include "Player.h"
#include "CharacterController.h"
#include <vector>

Player::Player(Window* window, Renderer* renderer, Material* material) : Entity(renderer) {
	m_window = window;

	m_tag = "Player";

	m_texture = new Texture("characters.bmp");
	m_texture->SetTextureDimensions(736, 128);
	m_texture->SetFrameDimensions(32, 32);
	m_texture->SetNumberOfFramesPerRow(23);
	m_texture->SetNumberOfFramesPerColumn(4);

	m_sprite = new Sprite(renderer, material, m_texture);
	m_sprite->SetFrameID(25);

	std::vector<int> idleAnimFrames = { 36 };
	m_sprite->AddAnimation("idle", idleAnimFrames);

	std::vector<int> runAnimFrames = { 34, 35, 36, 37, 38, 39, 40, 41, 42 };
	m_sprite->AddAnimation("run", runAnimFrames);

	std::vector<int> notGroundedAnimFrames = { 35 };
	m_sprite->AddAnimation("notGrounded", notGroundedAnimFrames);

	m_collider = new BoxCollider(m_texture->GetFrameWidth(), m_texture->GetFrameHeight());

	m_controller = new CharacterController(m_window, this);
	m_controller->GetMovementComponent()->SetAcceleration(20.0f);
	m_controller->GetMovementComponent()->SetDragValue(0.1f);
	m_controller->GetMovementComponent()->SetMaxSpeed(500);
	m_controller->SetJumpParamenters(0.1f, 300.0f);

	m_state = State::IDLE;
}


Player::~Player() {
	if (m_texture != nullptr) delete m_texture;
	if (m_sprite != nullptr) delete m_sprite;
	if (m_collider != nullptr) delete m_collider;
	if (m_controller != nullptr) delete m_controller;
}

void Player::Update(float deltaTime) {
	if (m_enabled) {
		m_controller->Update(deltaTime);

		m_sprite->SetModelMatrix(m_ModelMat);
		m_sprite->Update(deltaTime);

		UpdateState(deltaTime);
	}
}

void Player::UpdateState(float deltaTime) {
	float velocity_x = m_controller->GetMovementComponent()->GetVelocity().x;
	bool isGrounded = GetBoxCollider()->GetCollisionFlag().bottom;

	if (velocity_x < 0)
		SetScale(-1.0f, GetScale().y, GetScale().z);
	else
		SetScale(1.0f, GetScale().y, GetScale().z);

	switch (m_state) {
	case State::IDLE:
		m_sprite->SetAnimation("idle");
		if ((int)velocity_x != 0)
			m_state = State::RUN;
		if (!isGrounded)
			m_state = State::NOT_GROUNDED;
		break;
	case State::RUN:
		m_sprite->SetAnimation("run");
		if ((int)velocity_x == 0)
			m_state = State::IDLE;
		if (!isGrounded)
			m_state = State::NOT_GROUNDED;
		break;
	case State::NOT_GROUNDED:
		m_sprite->SetAnimation("notGrounded");
		if (isGrounded)
			m_state = State::IDLE;
		break;
	case State::KILLED:
		break;
	}

	if (GetBoxCollider()->GetCollisionFlag().left || GetBoxCollider()->GetCollisionFlag().right) {
		Entity* collidingEnity = GetBoxCollider()->GetCollidingEntity();
		if (collidingEnity != nullptr && collidingEnity->GetTag() == "Enemy") {
			m_enabled = false;
		}
	}
	m_sprite->PlayAnimation(deltaTime);
}
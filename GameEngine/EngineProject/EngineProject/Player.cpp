#include "Player.h"
#include "CharacterController.h"


Player::Player(Window* window, Renderer* renderer, Material* material) : Entity(renderer) {
	m_window = window;

	m_texture = new Texture("characters.bmp");
	m_texture->SetTextureDimensions(736, 128);
	m_texture->SetFrameDimensions(32, 32);
	m_texture->SetNumberOfFramesPerRow(24);
	m_texture->SetNumberOfFramesPerColumn(4);

	m_sprite = new Sprite(renderer, material, m_texture);
	m_sprite->SetFrameID(25);

	m_collider = new BoxCollider(m_texture->GetFrameWidth(), m_texture->GetFrameHeight());

	m_controller = new CharacterController(m_window, this);
}


Player::~Player() {
	if (m_texture != nullptr) delete m_texture;
	if (m_sprite != nullptr) delete m_sprite;
	if (m_collider != nullptr) delete m_collider;
}

void Player::Update(float deltaTime) {
	m_sprite->SetModelMatrix(m_ModelMat);
	m_controller->Update(deltaTime);

	Draw();
}

void Player::Draw() {
	m_sprite->Draw();
}
#include "Game.h"

Game::Game(const int& widht, const int& height, const char* name)
	: GameBase(widht, height, name) {	
}

Game::~Game() {
	if (m_sprite != nullptr)
		delete m_sprite;

	if (m_material != nullptr)
		delete m_material;

	if (m_texture != nullptr)
		delete m_texture;
	
	if (m_tilemapTexture != nullptr)
		delete m_tilemapTexture;

	if (m_tilemap != nullptr)
		delete m_tilemap;
}


bool Game::OnStart() {
	m_material = new Material();

	m_tilemapTexture = new Texture("tilemap2.bmp");
	m_tilemapTexture->SetTextureDimensions(64, 64);
	m_tilemapTexture->SetFrameDimensions(32, 32);
	m_tilemapTexture->SetNumberOfFramesPerRow(2);
	m_tilemapTexture->SetNumberOfFramesPerColumn(2);

	m_tilemap = new Tilemap(m_renderer, m_window->GetWidth(), m_window->GetHeight());
	m_tilemap->SetMaterial(m_material);
	m_tilemap->SetTexture(m_tilemapTexture);
	m_tilemap->SetPos(
		0.0f,
		m_window->GetHeight(),
		0.0f
	);

	m_texture = new Texture("uvtemplate.bmp");
	m_texture->SetTextureDimensions(512, 512);
	m_texture->SetFrameDimensions(51, 51);
	m_texture->SetNumberOfFramesPerRow(10);
	m_texture->SetNumberOfFramesPerColumn(10);

	m_sprite = new Sprite(m_renderer);
	m_sprite->SetMaterial(m_material);
	m_sprite->SetTexture(m_texture);
	m_sprite->InitVertices();
	m_sprite->SetFrameID(1);
	m_sprite->AddBoxCollider();
	m_sprite->SetPos(
		m_window->GetWidth() / 2, 
		m_window->GetHeight() / 2,
		0.0f
	);

	return true;
}

bool Game::OnStop() {
	return false;
}

bool Game::OnUpdate(float deltaTime) {
	m_sprite->HandleInput(m_window, deltaTime);
	m_tilemap->CheckCollisionWith(m_sprite);

	m_sprite->Draw();
	m_tilemap->Draw();
	return true;
}
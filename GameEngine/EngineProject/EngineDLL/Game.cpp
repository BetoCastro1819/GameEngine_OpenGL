#include "Game.h"

Game::Game(const int& widht, const int& height, const char* name)
	: GameBase(widht, height, name) {	
}

Game::~Game() {
	//if (m_sprite != nullptr)
	//	delete m_sprite;
	//
	//if (m_sprite2 != nullptr)
	//	delete m_sprite2;
	//
	//
	//if (m_texture != nullptr)
	//	delete m_texture;
	
	if (m_material != nullptr) delete m_material;
	if (m_tilemapTexture != nullptr) delete m_tilemapTexture;
	if (m_tilemap != nullptr) delete m_tilemap;
	if (m_player != nullptr) delete m_player;
}


bool Game::OnStart() {
	InitMaterials();
	InitTextures();
	InitEntities();
	SetupCollisionManager();

	return true;
}


bool Game::InitMaterials() {
	m_material = new Material();
	return true;
}	 

bool Game::InitTextures() {
	m_tilemapTexture = new Texture("tilemap2.bmp");
	m_tilemapTexture->SetTextureDimensions(64, 64);
	m_tilemapTexture->SetFrameDimensions(32, 32);
	m_tilemapTexture->SetNumberOfFramesPerRow(2);
	m_tilemapTexture->SetNumberOfFramesPerColumn(2);

	//m_texture = new Texture("characters.bmp");
	//m_texture->SetTextureDimensions(736, 128);
	//m_texture->SetFrameDimensions(32, 32);
	//m_texture->SetNumberOfFramesPerRow(24);
	//m_texture->SetNumberOfFramesPerColumn(4);

	return true;
}


bool Game::InitEntities() {
	m_tilemap = new Tilemap(m_renderer);
	m_tilemap->Setup(m_window, m_material, m_tilemapTexture);


	m_player = new Player(m_window, m_renderer, m_material);
	m_player->SetPos(m_window->GetWidth() / 2, m_window->GetHeight() / 2, 0);
	m_entities.push_back(m_player);

	//m_sprite = new Sprite(m_renderer, m_material, m_texture);
	//m_sprite->SetFrameID(25);
	//m_sprite->AddBoxCollider();
	//m_sprite->SetPos(
	//	m_window->GetWidth() / 2,
	//	m_window->GetHeight() / 2,
	//	0.0f
	//);
	//m_entities.push_back(m_sprite);
	//
	//m_sprite2 = new Sprite(m_renderer, m_material, m_texture);
	//m_sprite2->SetFrameID(73);
	//m_sprite2->AddBoxCollider();
	//m_sprite2->SetPos(
	//	m_window->GetWidth() / 5,
	//	m_window->GetHeight() / 2,
	//	0.0f
	//);
	//m_entities.push_back(m_sprite2);

	return true;
}

void Game::SetupCollisionManager() {
	m_collisionManager = CollisionManager::GetInstance();
	m_collisionManager->AddToGroup(CollisionLayer::PLAYER, m_player);
	//m_collisionManager->AddToGroup(CollisionLayer::DEFAULT, m_sprite2);
}

bool Game::OnUpdate(float deltaTime) {
	Input(deltaTime);
	UpdateEntities(deltaTime);
	DrawEntities(deltaTime);

	return true;
}

void Game::Input(float deltaTime) {
	//m_sprite->HandleInput(m_window, deltaTime);
}

void Game::UpdateEntities(float deltaTime) {
	m_collisionManager->CheckForCollisions();
	m_tilemap->HandleCollisions(m_entities);

	m_player->Update(deltaTime);
}

void Game::DrawEntities(float deltaTime) {
	//m_sprite->Draw();
	//m_sprite2->Draw();
	m_tilemap->Draw();
}

bool Game::OnStop() {
	return false;
}

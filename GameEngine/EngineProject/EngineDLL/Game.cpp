#include "Game.h"

Game::Game(const int& widht, const int& height, const char* name)
	: GameBase(widht, height, name) {	
}

Game::~Game() {
	if (m_material != nullptr) delete m_material;
	if (m_tilemapTexture != nullptr) delete m_tilemapTexture;
	if (m_tilemap != nullptr) delete m_tilemap;
	if (m_player != nullptr) delete m_player;
	if (m_enemy != nullptr) delete m_enemy;
}


bool Game::OnStart() {
	m_material = new Material();
	SetupTilemapTexture();
	InitEntities();
	SetupCollisionManager();

	return true;
}

bool Game::SetupTilemapTexture() {
	m_tilemapTexture = new Texture("tilemap2.bmp");
	m_tilemapTexture->SetTextureDimensions(64, 64);
	m_tilemapTexture->SetFrameDimensions(32, 32);
	m_tilemapTexture->SetNumberOfFramesPerRow(2);
	m_tilemapTexture->SetNumberOfFramesPerColumn(2);

	return true;
}


bool Game::InitEntities() {
	m_tilemap = new Tilemap(m_renderer);
	m_tilemap->Setup(m_window, m_material, m_tilemapTexture);

	m_player = new Player(m_window, m_renderer, m_material);
	m_player->SetPos(m_window->GetWidth() / 2, m_window->GetHeight() / 2, 0);
	m_entities.push_back(m_player);

	m_enemy = new Enemy(m_renderer, m_material);
	m_enemy->SetPos(m_window->GetWidth() / 5, m_window->GetHeight() / 2, 0);
	m_entities.push_back(m_enemy);

	return true;
}

void Game::SetupCollisionManager() {
	m_collisionManager = CollisionManager::GetInstance();
	m_collisionManager->AddToGroup(CollisionLayer::PLAYER, m_player);
	m_collisionManager->AddToGroup(CollisionLayer::DEFAULT, m_enemy);
}

bool Game::OnUpdate(float deltaTime) {
	Update(deltaTime);
	return true;
}

void Game::Update(float deltaTime) {
	m_tilemap->HandleCollisions(m_entities);
	m_collisionManager->CheckForCollisions();

	m_player->Update(deltaTime);
	m_enemy->Update(deltaTime);
	m_tilemap->Update(deltaTime);
}

bool Game::OnStop() {
	return false;
}

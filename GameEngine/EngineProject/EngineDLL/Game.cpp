#include "Game.h"

Game::Game(const int& widht, const int& height, const char* name)
	: GameBase(widht, height, name) {	
}

Game::~Game() {
	if (m_material != nullptr) delete m_material;
	if (m_tilemapTexture != nullptr) delete m_tilemapTexture;
	if (m_tilemap != nullptr) delete m_tilemap;
	if (m_player != nullptr) delete m_player;

	for (int i = 0; i < ENEMY_SIZE; i++) {
		if (m_enemy[i] != nullptr) delete m_enemy[i];
	}
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
	m_tilemap = new Tilemap(m_renderer, "level.json");
	m_tilemap->Setup(m_window, m_material, m_tilemapTexture);

	m_player = new Player(m_window, m_renderer, m_material);
	m_player->SetPos(m_window->GetWidth() / 2, m_window->GetHeight() / 2, 0);
	m_player->SetRespawnPosition(m_player->GetPos());
	m_entities.push_back(m_player);

	for (int i = 0; i < ENEMY_SIZE; i++) {
		m_enemy[i] = new Enemy(m_renderer, m_material);
		m_entities.push_back(m_enemy[i]);
	}
	SetupEnemiesPositions();
	return true;
}

void Game::SetupCollisionManager() {
	m_collisionManager = CollisionManager::GetInstance();
	m_collisionManager->AddToGroup(CollisionLayer::PLAYER, m_player);
	for (int i = 0; i < ENEMY_SIZE; i++) {
		m_collisionManager->AddToGroup(CollisionLayer::DEFAULT, m_enemy[i]);
	}
}

void Game::SetupEnemiesPositions() {
	m_enemy[0]->SetPos(32 * 33, 32 * 4, 0);
	m_enemy[1]->SetPos(32 * 55, 32 * 4, 0);
	m_enemy[2]->SetPos(32 * 66, 32 * 4, 0);
}

bool Game::OnUpdate(float deltaTime) {
	if (m_player->GetIsEnabled()) {
		Update(deltaTime);
		m_renderer->SetCameraPosition(m_player->GetPos().x - m_window->GetWidth() / 2, 0, 4);
	}
	else {
		Reset();
	}

	return true;
}

void Game::Update(float deltaTime) {
	m_tilemap->HandleCollisions(m_entities);
	m_collisionManager->CheckForCollisions();

	m_player->Update(deltaTime);
	if (m_player->GetPos().y < -m_player->GetBoxCollider()->GetBoxHeight())
		m_player->SetIsEnabled(false);

	for (int i = 0; i < ENEMY_SIZE; i++) {
		m_enemy[i]->Update(deltaTime);
	}

	m_tilemap->Update(deltaTime);
}

void Game::Reset() {
	m_player->Respawn();
	SetupEnemiesPositions();

	for (int i = 0; i < ENEMY_SIZE; i++)
		m_enemy[i]->Reset();
}

bool Game::OnStop() {
	return false;
}

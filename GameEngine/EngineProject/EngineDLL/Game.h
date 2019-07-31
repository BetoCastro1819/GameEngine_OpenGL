#pragma once
#include <iostream>
#include "GameBase.h"
#include "Material.h"
#include "Sprite.h"
#include "Texture.h"
#include "Tilemap.h"
#include "CollisionManager.h"
#include "..\EngineProject\Player.h"
#include "..\EngineProject\Enemy.h"

using namespace std;

const int ENEMY_SIZE = 3;

class Game : public GameBase {
private:
	CollisionManager* m_collisionManager;
	Material* m_material;
	Texture* m_tilemapTexture;
	Tilemap* m_tilemap;
	Player* m_player;
	Enemy* m_enemy[ENEMY_SIZE];

	vector<Entity*> m_entities;

	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate(float deltaTime) override;

	bool SetupTilemapTexture();
	bool InitEntities();
	void SetupCollisionManager();
	void SetupEnemiesPositions();

	void Reset();

	void Update(float delaTime);

public:
	Game(const int& height, const int& widht, const char* name);
	~Game();
};


#pragma once
#include <iostream>
#include "GameBase.h"
#include "Material.h"
#include "Sprite.h"
#include "Texture.h"
#include "Tilemap.h"
#include "CollisionManager.h"

using namespace std;

class Game : public GameBase {
private:
	CollisionManager* m_collisionManager;
	Material* m_material;
	Texture* m_tilemapTexture;
	Texture* m_texture;
	Tilemap* m_tilemap;
	Sprite* m_sprite;
	Sprite* m_sprite2;

	vector<Sprite*> m_entities;

	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate(float deltaTime) override;

	bool InitMaterials();
	bool InitTextures();
	bool InitEntities();
	void SetupCollisionManager();

	void Input(float deltaTime);
	void UpdateEntities(float delaTime);
	void DrawEntities(float deltaTime);


public:
	Game(const int& height, const int& widht, const char* name);
	~Game();
};


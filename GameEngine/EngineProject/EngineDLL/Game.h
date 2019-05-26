#pragma once
#include <iostream>
#include "GameBase.h"
#include "Material.h"
#include "Sprite.h"
#include "Texture.h"
#include "Tilemap.h"

using namespace std;

class Game : public GameBase {
protected:
	Material* m_material;
	Texture* m_tilemapTexture;
	Texture* m_texture;
	Tilemap* m_tilemap;
	Sprite* m_sprite;
	Sprite* m_sprite2;

	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate(float deltaTime) override;

public:
	Game(const int& height, const int& widht, const char* name);
	~Game();
};


#pragma once
#include "Exports.h"
#include "Shape.h"
#include "Renderer.h"
#include "Texture.h"
#include "Sprite.h"
#include <vector>

using namespace std;

class ENGINEDLL_API Tilemap : public Shape {
private:
	Texture* m_texture;
	unsigned int m_textureID;

	//unsigned int m_Texture;
	int m_ScreenWidth;
	int m_ScreenHeight;

	int m_TileWidth;
	int m_TileHeight;

	int m_TextureHeight;
	int m_TextureWidth;
	int m_TotalTilesPerRow;

	vector<float> m_VertexArrayPos;
	vector<float> m_VertexArrayUV;
	vector<int> m_CollidableTilesIndexes;

	struct TilemapData {
		int tilesPerRow;
		int tilesPerCol;
		int tileHeight;
		int tileWidth;
		vector<int> tiles;
	} m_TilesData;

public:
	Tilemap(Renderer* renderer, int screenWidth, int screenHeight);
	~Tilemap();

	// Variables
	unsigned int m_uvBufferData;
	vector<vector<int>> indexes;

	void Draw() override;
	void SetMaterial(Material* material) override;

	void SetTexture(Texture* texture);
	void SetVerticesUV(float* vertices);
	float GetOffsetX(unsigned int id);
	float GetOffsetY(unsigned int id);

	void CheckCollisionWith(Sprite* sprite);
	void SetColliderTiles(vector<int> setOfIds);

	float GetTileX(float x);
	float GetTileY(float y);
};
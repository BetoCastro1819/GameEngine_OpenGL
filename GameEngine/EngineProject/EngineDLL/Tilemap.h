#pragma once
#include "Exports.h"
#include "Shape.h"
#include "Renderer.h"
#include <vector>

using namespace std;

class ENGINEDLL_API Tilemap : public Shape {
private:
	unsigned int m_Texture;
	int m_ScreenWidth;
	int m_ScreenHeight;

	int m_TileWidth;
	int m_TileHeight;

	int m_TextureHeight;
	int m_TextureWidth;
	int m_TextureTilesPerRow;

	vector<float> m_VertexArrayPos;
	vector<float> m_VertexArrayUV;
	vector<int> m_CollidableTiles;

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
	unsigned int verticesUV;
	vector<vector<int>> indexes;


	void Draw() override {}
	void SetMaterial(Material* material) override {}

	void SetTexture(const char* filePath);
	void SetVerticesUV(float* vertices);
	void SetFrameType(int frameWidth, int frameHeight, int framesPerRow);
	float GetOffsetX(unsigned int id);
	float GetOffsetY(unsigned int id);
	void SetColliderTiles(vector<int> setOfIds);
	bool NextTileIsCollider(float x, float y);
	float GetTileX(float x);
	float GetTileY(float y);
};



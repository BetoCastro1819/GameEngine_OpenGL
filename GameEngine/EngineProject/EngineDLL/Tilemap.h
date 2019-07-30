#pragma once
#include "Exports.h"
#include "Shape.h"
#include "Renderer.h"
#include "Texture.h"
#include "Sprite.h"
#include "Window.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>


using namespace std;

class ENGINEDLL_API Tilemap : public Shape {
private:
	Texture* m_texture;
	unsigned int m_textureID;

	vector<float> m_VertexArrayPos;
	vector<float> m_VertexArrayUV;
	vector<int> m_CollidableTilesIndexes;
	vector<glm::vec3> m_tilesPositions;

	int m_tileWidth;
	int m_tileHeight;

	unsigned int m_uvBufferData;
	//vector<vector<int>> indexes;

	struct TilemapData {
		int tilesPerRow;
		int tilesPerCol;
		int tileHeight;
		int tileWidth;
		vector<int> tilesIndexes;
	} m_TilesData;

	void SetupDataFromJSON(const char* jsonFilePath);
	void SetMaterial(Material* material) override;
	void SetTexture(Texture* texture);
	void SetupVertexArray();
	void SetupVertexArrayUV();
	void SetVerticesUV(float* vertices);
	void SetupTilesPositions();

	float GetOffsetX(unsigned int id);
	float GetOffsetY(unsigned int id);
	float GetTileX(float x);
	float GetTileY(float y);

	bool OnCollisionWith(Entity* sprite, glm::vec3 tilePosition) const;

public:
	Tilemap(Renderer* renderer, const char* jsonFilePath);
	~Tilemap() { }

	void Setup(Window* window, Material* material, Texture* texture);
	void Update(float) override;
	void HandleCollisions(vector<Entity*> entities);
	void SetColliderTiles(vector<int> setOfIds);
};
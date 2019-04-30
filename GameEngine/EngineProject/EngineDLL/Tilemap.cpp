#include "Tilemap.h"
#include <GL\glew.h>
#include "json.hpp"
#include <fstream>

Tilemap::Tilemap(Renderer* renderer, int screenWidth, int screenHeight) : Shape(renderer) {
	m_renderer = renderer;
	m_ScreenWidth = screenWidth;
	m_ScreenHeight = screenHeight;


	ifstream tilemapJSON("tilemap.json");
	nlohmann::json jsonParsedData;
	jsonParsedData = nlohmann::json::parse(tilemapJSON);
	m_TilesData.tileHeight = jsonParsedData["tileheight"];
	m_TilesData.tileWidth = jsonParsedData["tilewidth"];
	m_TilesData.tilesPerRow = jsonParsedData["width"];
	m_TilesData.tilesPerCol = jsonParsedData["height"];
	vector<int> v = jsonParsedData["layers"][0]["data"];
	m_TilesData.tiles = v;

	m_ModelMat = glm::mat4(1.0f);

	m_TotalTilesPerRow = 0;
}

Tilemap::~Tilemap() {
}

void Tilemap::SetMaterial(Material* material) {
	m_material = material;
	m_programID = m_material->LoadShaders("TextureVertexShader.txt", "TextureFragmentShader.txt");
}

void Tilemap::SetTexture(const char* imagePath) {
	if (m_material)
		m_Texture = m_material->Load_BMP(imagePath);
	else
		printf("m_Material in Tilemap is NULL");

	m_TileHeight = m_TilesData.tileHeight;
	m_TileWidth = m_TilesData.tileWidth;
	m_TextureHeight = 512;
	m_TextureWidth = 512;
	indexes = vector<vector<int>>(m_TilesData.tilesPerCol, vector<int>(m_TilesData.tilesPerRow));

	int numberOfIndexes = 0;
	for (int i = 0; i < indexes.size(); i++) {
		for (int j = 0; j < indexes[0].size(); j++) {
			indexes[i][j] = m_TilesData.tiles[numberOfIndexes] - 1;
			numberOfIndexes++;
		}
	}

	for (int i = 0; i < indexes.size(); i++) {
		for (int j = 0; j < indexes[0].size(); j++) {
			int col = j * m_TileWidth;
			int row = i * m_TileHeight;

			m_VertexArrayPos.push_back(0.0f + col);
			m_VertexArrayPos.push_back(-m_TileHeight - row);
			m_VertexArrayPos.push_back(0.0f);

			m_VertexArrayPos.push_back(m_TileWidth + col);
			m_VertexArrayPos.push_back(-m_TileHeight - row);
			m_VertexArrayPos.push_back(0.0f);

			m_VertexArrayPos.push_back(m_TileWidth + col);
			m_VertexArrayPos.push_back(0.0f - row);
			m_VertexArrayPos.push_back(0.0f);

			m_VertexArrayPos.push_back(0.0f + col);
			m_VertexArrayPos.push_back(0.0f - row);
			m_VertexArrayPos.push_back(0.0f);
		}
	}
	float* p = &m_VertexArrayPos[0];
	SetVertices(p, 4 * indexes.size()*indexes[0].size());


	for (int i = 0; i < indexes.size(); i++) {
		for (int j = 0; j < indexes[0].size(); j++) {
			int id = indexes[i][j];

			// 00
			m_VertexArrayUV.push_back(GetOffsetX(id) / m_TextureWidth);
			m_VertexArrayUV.push_back(1 - (GetOffsetY(id) + m_TileHeight) / m_TextureHeight);
			// 10
			m_VertexArrayUV.push_back((GetOffsetX(id) + m_TileWidth) / m_TextureWidth);
			m_VertexArrayUV.push_back(1 - (GetOffsetY(id) + m_TileHeight) / m_TextureHeight);
			// 11
			m_VertexArrayUV.push_back((GetOffsetX(id) + m_TileWidth) / m_TextureWidth);
			m_VertexArrayUV.push_back(1 - GetOffsetY(id) / m_TextureHeight);
			// 01
			m_VertexArrayUV.push_back(GetOffsetX(id) / m_TextureWidth);
			m_VertexArrayUV.push_back(1 - (GetOffsetY(id) / m_TextureHeight));
		}
	}
	p = &m_VertexArrayUV[0];
	SetVerticesUV(p);
}

void Tilemap::Draw() {
	m_renderer->LoadIdentityMatrix();
	m_renderer->MultiplyModelMatrix(m_ModelMat);
	if (m_material) {
		BindMaterial();
		m_material->SetMatrixProperty("MVP", m_renderer->GetMVP());
		m_material->SetTextureProperty("myTextureSampler", m_Texture);
	}
	m_renderer->BindBuffer(m_BufferData, m_VtxCount, 0, 3, 3);
	m_renderer->BindBuffer(verticesUV, m_VtxCount, 1, 2, 3);
}

void Tilemap::SetFrameType(int frameWidth, int frameHeight, int framesCountPerRow) {
	//m_TileWidth = frameWidth;
	//m_TileHeight = frameHeight;
	m_TotalTilesPerRow = framesCountPerRow;
}

float Tilemap::GetOffsetX(unsigned int id) {
	return (id % m_TotalTilesPerRow) * m_TileWidth;
}

float Tilemap::GetOffsetY(unsigned int id) {
	return (id / m_TotalTilesPerRow) * m_TileHeight;
}

void Tilemap::SetVerticesUV(float* vertices) {
	verticesUV = (m_renderer->GenBuffer(vertices, m_VtxCount * 2 * sizeof(float)));
}

bool Tilemap::NextTileIsCollider(float x, float y) {
	int tileID;

	x = (x - GetPos().x);
	y = -(y + GetPos().y);

	if (x >= 0 && y >= 0) {
		int col = x / m_TileWidth;
		int row = y / m_TileHeight;

		int temp = indexes.size();
		if (col >= 0 && col < indexes[0].size() && row >= 0 && row < temp) {
			tileID = indexes[row][col];
			for (vector<int>::iterator it = m_CollidableTiles.begin(); it < m_CollidableTiles.end(); it++) {
				if (*it == tileID)
					return true;
			}
		}
	}
	return false;
}

void Tilemap::SetColliderTiles(vector<int> collidingTilesIndexes) {
	m_CollidableTiles = collidingTilesIndexes;
}

float Tilemap::GetTileX(float x) {
	int col = (x - GetPos().x) / m_TileWidth;
	return col * m_TileWidth + GetPos().x;
}

float Tilemap::GetTileY(float y) {
	int row = (y + GetPos().y) / m_TileHeight;
	return row * m_TileHeight - GetPos().y;
}


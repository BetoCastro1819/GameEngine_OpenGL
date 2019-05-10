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
	m_programID = m_material->LoadShaders("SimpleVertexShader.txt", "SimpleFragmentShader.txt");
}

void Tilemap::SetTexture(Texture* texture) {
	m_texture = texture;
	m_textureID = m_renderer->SetTextureID(m_programID);
	printf("Tilemap textureID: %d\n", m_textureID);

	m_TextureWidth = m_texture->GetWidth();
	m_TextureHeight = m_texture->GetHeight();
	m_TileHeight = m_texture->GetFrameHeight();
	m_TileWidth = m_texture->GetFrameWidth();
	m_TotalTilesPerRow = m_texture->GetFramesPerRow();

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
	BindMaterial();

	m_material->SetMatrixProperty("MVP", m_renderer->GetMVP());

	m_renderer->BindTexture(m_texture->GetTextureData());
	m_material->SetTextureProperty("myTextureSampler", m_textureID);

	// Vertex buffer
	m_renderer->EnableVertexAttribArray(0);
	m_renderer->BindBuffer(m_vertexBuffer);
	m_renderer->VertexAttribPointer(0, 3);

	// UV Vertex buffer
	m_renderer->EnableVertexAttribArray(1);
	m_renderer->BindBuffer(m_uvBufferData);
	m_renderer->VertexAttribPointer(1, 2);

	m_renderer->DrawArrays(3, m_numberOfVertices);

	m_renderer->DisableVertexArray(0);
	m_renderer->DisableVertexArray(1);

	m_renderer->UpdateModelMatrix(m_ModelMat);
	m_renderer->UpdateMVP();
}

void Tilemap::SetFrameType(int frameWidth, int frameHeight, int framesCountPerRow) {
	//m_TileWidth = frameWidth;
	//m_TileHeight = frameHeight;
	//m_TotalTilesPerRow = framesCountPerRow;
}

float Tilemap::GetOffsetX(unsigned int id) {
	return (id % m_TotalTilesPerRow) * m_TileWidth;
}

float Tilemap::GetOffsetY(unsigned int id) {
	return (id / m_TotalTilesPerRow) * m_TileHeight;
}

void Tilemap::SetVerticesUV(float* vertices) {
	m_uvBufferData = (m_renderer->GenBuffer(vertices, m_numberOfVertices * 2 * sizeof(float)));
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


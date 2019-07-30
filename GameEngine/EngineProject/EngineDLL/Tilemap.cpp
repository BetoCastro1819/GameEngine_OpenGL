#include "Tilemap.h"
#include "json.hpp"

#include <GL\glew.h>
#include <fstream>

Tilemap::Tilemap(Renderer* renderer, const char* jsonFilePath) : Shape(renderer) {
	m_renderer = renderer;
	SetupDataFromJSON(jsonFilePath);
}

void Tilemap::Setup(Window* window, Material* material, Texture* texture) {
	SetPos(0.0f, window->GetHeight(), 0.0f);
	SetMaterial(material);
	SetTexture(texture);
	SetupVertexArray();
	SetupVertexArrayUV();
	SetupTilesPositions();
}

void Tilemap::SetupDataFromJSON(const char* jsonFilePath) {
	ifstream tilemapJSON(jsonFilePath);
	nlohmann::json jsonParsedData = nlohmann::json::parse(tilemapJSON);

	m_TilesData.tileHeight = jsonParsedData["tileheight"];
	m_TilesData.tileWidth = jsonParsedData["tilewidth"];
	m_TilesData.tilesPerRow = jsonParsedData["width"];
	m_TilesData.tilesPerCol = jsonParsedData["height"];
	vector<int> indexes = jsonParsedData["layers"][0]["data"];
	m_TilesData.tilesIndexes = indexes;
}

void Tilemap::SetMaterial(Material* material) {
	m_material = material;
	m_programID = m_material->LoadShaders("SimpleVertexShader.txt", "SimpleFragmentShader.txt");
}

void Tilemap::SetTexture(Texture* texture) {
	m_texture = texture;
	m_textureID = texture->GetTextureID();
}

void Tilemap::SetupVertexArray() {
	m_tileHeight = m_texture->GetFrameHeight();
	m_tileWidth = m_texture->GetFrameWidth();

	for (int i = 0; i < m_TilesData.tilesPerCol; i++) {
		for (int j = 0; j < m_TilesData.tilesPerRow; j++) {
			int col = i * m_tileHeight;
			int row = j * m_tileWidth;

			m_VertexArrayPos.push_back(0.0f + row);
			m_VertexArrayPos.push_back(-m_tileHeight - col);
			m_VertexArrayPos.push_back(0.0f);

			m_VertexArrayPos.push_back(m_tileWidth + row);
			m_VertexArrayPos.push_back(-m_tileHeight - col);
			m_VertexArrayPos.push_back(0.0f);

			m_VertexArrayPos.push_back(m_tileWidth + row);
			m_VertexArrayPos.push_back(0.0f - col);
			m_VertexArrayPos.push_back(0.0f);

			m_VertexArrayPos.push_back(0.0f + row);
			m_VertexArrayPos.push_back(0.0f - col);
			m_VertexArrayPos.push_back(0.0f);
		}
	}
	SetVertices(&m_VertexArrayPos[0], 4 * m_TilesData.tilesPerCol * m_TilesData.tilesPerRow);
}

void Tilemap::SetupVertexArrayUV() {
	float textureWidth = m_texture->GetWidth();
	float textureHeight = m_texture->GetHeight();

	for (int i = 0; i < m_TilesData.tilesPerCol * m_TilesData.tilesPerRow; i++) {
		int id = m_TilesData.tilesIndexes[i] - 1;

		// 00
		m_VertexArrayUV.push_back(GetOffsetX(id) / textureWidth);
		m_VertexArrayUV.push_back(1 - (GetOffsetY(id) + m_tileHeight) / textureHeight);
		// 10
		m_VertexArrayUV.push_back((GetOffsetX(id) + m_tileWidth) / textureWidth);
		m_VertexArrayUV.push_back(1 - (GetOffsetY(id) + m_tileHeight) / textureHeight);
		// 11
		m_VertexArrayUV.push_back((GetOffsetX(id) + m_tileWidth) / textureWidth);
		m_VertexArrayUV.push_back(1 - GetOffsetY(id) / textureHeight);
		// 01
		m_VertexArrayUV.push_back(GetOffsetX(id) / textureWidth);
		m_VertexArrayUV.push_back(1 - (GetOffsetY(id) / textureHeight));
	}
	SetVerticesUV(&m_VertexArrayUV[0]);
}

void Tilemap::SetupTilesPositions() {
	for (int col = 0; col < m_TilesData.tilesPerCol; col++) {
		for (int row = 0; row < m_TilesData.tilesPerRow; row++) {
			glm::vec3 tilePosition = glm::vec3(
				GetPos().x + (m_tileWidth * row) + m_tileWidth / 2,
				GetPos().y - (m_tileHeight * col) - m_tileHeight / 2,
				GetPos().z
			);
			m_tilesPositions.push_back(tilePosition);
		}
	}
}

void Tilemap::Update(float deltaTime) {
	m_renderer->UpdateModelMatrix(m_ModelMat);
	m_renderer->UpdateMVP();

	BindMaterial();

	m_material->SetMatrixProperty("MVP", m_renderer->GetMVP());

	m_renderer->BindTexture(m_texture->GetTextureID());
	m_material->SetTextureProperty("myTextureSampler", m_textureID);

	m_renderer->EnableVertexAttribArray(0);
	m_renderer->BindBuffer(m_vertexBuffer);
	m_renderer->VertexAttribPointer(0, 3);

	m_renderer->EnableVertexAttribArray(1);
	m_renderer->BindBuffer(m_uvBufferData);
	m_renderer->VertexAttribPointer(1, 2);

	m_renderer->DrawArrays(3, m_numberOfVertices);

	m_renderer->DisableVertexArray(0);
	m_renderer->DisableVertexArray(1);
}

void Tilemap::HandleCollisions(vector<Entity*> entities) {

	for (int entityIndex = 0; entityIndex < entities.size(); entityIndex++) {
		entities[entityIndex]->GetBoxCollider()->SetCollisionFlag_bottom(false);
		entities[entityIndex]->GetBoxCollider()->SetCollisionFlag_top(false);
		entities[entityIndex]->GetBoxCollider()->SetCollisionFlag_left(false);
		entities[entityIndex]->GetBoxCollider()->SetCollisionFlag_right(false);

		for (int i = 0; i < m_tilesPositions.size(); i++) {
			if (m_TilesData.tilesIndexes[i] == 2) {
				OnCollisionWith(entities[entityIndex], m_tilesPositions[i]);
			}
		}
	}
}



bool Tilemap::OnCollisionWith(Entity* entity, glm::vec3 tilePosition) const {
	glm::vec3 diff;
	diff = tilePosition - entity->GetPos();

	float modX = glm::abs(diff.x);
	float modY = glm::abs(diff.y);

	if (modX < entity->GetBoxCollider()->GetBoxWidth() / 2 + m_tileWidth / 2 &&
		modY < entity->GetBoxCollider()->GetBoxHeight() / 2 + m_tileHeight / 2) {

		float penX = entity->GetBoxCollider()->GetBoxWidth() / 2 + m_tileWidth / 2 - modX;
		float penY = entity->GetBoxCollider()->GetBoxHeight() / 2 + m_tileHeight / 2 - modY;

		if (penX > penY) {
			if (entity->GetPos().y < tilePosition.y) {
				entity->Translate(0, -penY, 0);
				entity->GetBoxCollider()->SetCollisionFlag_top(true);
			}
			else {
				entity->Translate(0, penY, 0);
				entity->GetBoxCollider()->SetCollisionFlag_bottom(true);
			}
			return true;
		}
		else {
			if (entity->GetPos().x < tilePosition.x) {
				entity->Translate(-penX, 0, 0);
				entity->GetBoxCollider()->SetCollisionFlag_right(true);
			}
			else {
				entity->Translate(penX, 0, 0);
				entity->GetBoxCollider()->SetCollisionFlag_left(true);
			}
			return true;
		}
	}
	return false;
}

float Tilemap::GetOffsetX(unsigned int id) {
	return (id % m_texture->GetFramesPerRow()) * m_tileWidth;
}

float Tilemap::GetOffsetY(unsigned int id) {
	return (id / m_texture->GetFramesPerRow()) * m_tileHeight;
}

void Tilemap::SetVerticesUV(float* vertices) {
	m_uvBufferData = (m_renderer->GenBuffer(vertices, m_numberOfVertices * 2 * sizeof(float)));
}

void Tilemap::SetColliderTiles(vector<int> collidableTilesIndexes) {
	m_CollidableTilesIndexes = collidableTilesIndexes;
}

float Tilemap::GetTileX(float x) {
	int col = (x - GetPos().x) / m_tileWidth;
	return col * m_tileWidth + GetPos().x;
}

float Tilemap::GetTileY(float y) {
	int row = (y + GetPos().y) / m_tileHeight;
	return row * m_tileHeight - GetPos().y;
}


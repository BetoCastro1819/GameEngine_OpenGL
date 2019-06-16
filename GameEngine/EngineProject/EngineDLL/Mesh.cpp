#include "Mesh.h"
#include "OBJ_Loader.h"
#include "TextureLoader.h"
#include "Transform.h"
#include "Material.h"
#include "Renderer.h"
#include "Entity.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>


Mesh::Mesh(Entity* entity, Renderer* renderer, Material* material, const char* texturePath) : Component(entity) {
	SetType(ComponentType::MESH);

	m_renderer = renderer;

	m_material = material;
	SetShader(m_material->GetShaderID());

	SetTexture(texturePath);
}

void Mesh::SetShader(unsigned int programId) {
	m_programID = programId;
	m_lightID = m_renderer->GetLightHandleID(m_programID);
}

void Mesh::SetTexture(const char* filePath) {
	m_textureID = TextureLoader::LoadFromFile_BMP(filePath);
}

void Mesh::Update(float deltaTime) {
	Draw();
}

void Mesh::Draw() {
	m_renderer->UpdateModelMatrix(m_entity->GetTransform()->GetModelMatrix());
	m_renderer->UpdateMVP();

	m_renderer->BindMaterial(m_programID);

	m_material->SetMatrixProperty("MVP", m_renderer->GetMVP());

	m_renderer->BindTexture(m_textureID);
	m_renderer->SetTextureSampler(m_textureID);

	m_material->SetTextureProperty("myTextureSampler", m_textureID);
	
	m_renderer->EnableBuffer(0);
	m_renderer->BindBuffer(m_vertexBuffer);
	m_renderer->SetShaderData(0, 3);

	m_renderer->EnableBuffer(1);
	m_renderer->BindBuffer(m_uvBuffer);
	m_renderer->SetShaderData(1, 2);

	m_renderer->EnableBuffer(2);
	m_renderer->BindBuffer(m_normalBuffer);
	m_renderer->SetShaderData(2, 3);

	m_renderer->BindElementBuffer(m_elementsBuffer);

	m_renderer->DrawElements(m_indices.size());

	m_renderer->DisableVertexArrays(0);
	m_renderer->DisableVertexArrays(1);
	m_renderer->DisableVertexArrays(2);
}

bool Mesh::LoadWithAssimp(const char* filePath) {
	if (!OBJ_Loader::loadWithAssimp(
		filePath,
		m_indices,
		m_indexedVertices,
		m_indexedUVs,
		m_indexedNormals
	)) {
		return false;
	}
	GenerateBuffers();
	return true;
}

void Mesh::GenerateBuffers() {
	m_vertexBuffer = m_renderer->GenBuffer(&m_indexedVertices[0], m_indexedVertices.size() * sizeof(glm::vec3));
	m_uvBuffer = m_renderer->GenBuffer(&m_indexedUVs[0], m_indexedUVs.size() * sizeof(glm::vec2));
	m_normalBuffer = m_renderer->GenBuffer(&m_indexedNormals[0], m_indexedNormals.size() * sizeof(glm::vec3));
	m_elementsBuffer = m_renderer->GenElementsBuffer(&m_indices[0], m_indices.size() * sizeof(unsigned short));
}
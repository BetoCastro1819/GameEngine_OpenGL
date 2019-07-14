#include "Mesh.h"
#include "TextureLoader.h"
#include "Transform.h"
#include "Material.h"
#include "Renderer.h"
#include "Entity.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <assimp/Importer.hpp> 
#include <assimp/scene.h>           
#include <assimp/postprocess.h>


Mesh::Mesh(Entity* entity, Renderer* renderer, Material* material, const char* texturePath) : Component(entity) {
	SetType(ComponentType::MESH);
	m_renderer = renderer;
	m_material = material;
	SetShader(m_material->GetShaderID());
	SetTexture(texturePath);
	m_texturePath = texturePath;
}

Mesh::Mesh(Entity* entity, Renderer* renderer, Material* material, unsigned int textureID) : Component(entity) {
	SetType(ComponentType::MESH);
	m_renderer = renderer;
	m_material = material;
	SetShader(m_material->GetShaderID());
	m_textureID = textureID;
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

bool Mesh::LoadModel(const char* filePath) {
	if (!LoadModelWithAssimp(filePath)) 
		return false;
	return true;
}

bool Mesh::LoadModelWithAssimp(const char* filePath) {
	printf("\nImporting file using Assimp from %s\n\n", filePath);
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate| aiProcess_FlipUVs);
	if (!scene) {
		printf("ERROR\n");
		return false;
	}
	if (scene->mNumMeshes <= 0) return false;

	// Root node
	ProcessMesh(scene->mMeshes[0]);
	GenerateBuffers();
	printf("\ROOT node: %s\n", scene->mMeshes[0]->mName.data);
	
	for (int meshIndex = 1; meshIndex < scene->mNumMeshes; meshIndex++) {
		ProcessNode(scene->mRootNode->mChildren[meshIndex], scene, meshIndex);
	}

	printf("\nNumber of meshes found in %s: %d \n", filePath, scene->mNumMeshes);
}

void Mesh::ProcessNode(aiNode* node, const aiScene* scene, int& meshIndex) {
	Entity* newEntity = new Entity(m_renderer);
	newEntity->SetName(scene->mMeshes[meshIndex]->mName.data);
	
	printf("Node Nro.%d: %s\n", meshIndex, newEntity->GetName());

	Mesh* mesh = new Mesh(newEntity, m_renderer, m_material, m_textureID);
	mesh->ProcessMesh(scene->mMeshes[meshIndex]);
	mesh->GenerateBuffers();
	newEntity->AddComponent(mesh);

	m_entity->AddNode(newEntity);

	for (int nodeIndex = 0; nodeIndex < node->mNumChildren; nodeIndex++) {
		meshIndex++;
		ProcessNode(node->mChildren[nodeIndex], scene, meshIndex);
	}
}

void Mesh::ProcessMesh(aiMesh* mesh) {
	FillVBOinfo(mesh);
	FillFaceIndices(mesh);
}

void Mesh::FillVBOinfo(aiMesh* mesh) {
	m_indexedVertices.reserve(mesh->mNumVertices);
	m_indexedUVs.reserve(mesh->mNumVertices);
	m_indexedNormals.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D pos = mesh->mVertices[i];
		m_indexedVertices.push_back(glm::vec3(pos.x, pos.y, pos.z));

		aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		m_indexedUVs.push_back(glm::vec2(UVW.x, UVW.y));

		aiVector3D n = mesh->mNormals[i];
		m_indexedNormals.push_back(glm::vec3(n.x, n.y, n.z));
	}
}

void Mesh::FillFaceIndices(aiMesh* mesh) {
	m_indices.reserve(3 * mesh->mNumFaces);
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		m_indices.push_back(mesh->mFaces[i].mIndices[0]);
		m_indices.push_back(mesh->mFaces[i].mIndices[1]);
		m_indices.push_back(mesh->mFaces[i].mIndices[2]);
	}
}

void Mesh::GenerateBuffers() {
	m_vertexBuffer = m_renderer->GenBuffer(&m_indexedVertices[0], m_indexedVertices.size() * sizeof(glm::vec3));
	m_uvBuffer = m_renderer->GenBuffer(&m_indexedUVs[0], m_indexedUVs.size() * sizeof(glm::vec2));
	m_normalBuffer = m_renderer->GenBuffer(&m_indexedNormals[0], m_indexedNormals.size() * sizeof(glm::vec3));
	m_elementsBuffer = m_renderer->GenElementsBuffer(&m_indices[0], m_indices.size() * sizeof(unsigned short));
}


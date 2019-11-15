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
}

void Mesh::SetTexture(const char* filePath) {
	m_textureID = TextureLoader::LoadFromFile_BMP(filePath);
}

void Mesh::Update(float deltaTime) {
	if (m_entity->isInsideFrustrum()) {
		Draw();
	}
}

void Mesh::Draw() {

	m_renderer->UpdateModelMatrix(m_entity->GetTransform()->GetWorldMatrix());
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
	
	m_renderer->LoadIdentityMatrix();
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

	
	int meshIndex = 0;
	aiNode* rootNode = scene->mRootNode->mChildren[0];
	ProcessNode(rootNode, scene, meshIndex);

	printf("\nNumber of meshes found in %s: %d \n", filePath, scene->mNumMeshes);

	return true;
}

void Mesh::ProcessNode(aiNode* node, const aiScene* scene, int& meshIndex) {
	if (meshIndex >= scene->mNumMeshes) return; // 0;

	if (meshIndex == 0) {
		m_entity->SetName(node->mName.data);
		printf("\nROOT node: %s\n", m_entity->GetName());
		printf("Number of children: %d\n", node->mNumChildren);

		AttachMeshToEntity(scene->mMeshes[meshIndex]);
		
		meshIndex++;
		for (int nodeIndex = 0; nodeIndex < node->mNumChildren; nodeIndex++) {
			ProcessNode(node->mChildren[nodeIndex], scene, meshIndex);
		}
	}
	else {

		Entity* newEntity = new Entity(m_renderer);
		newEntity->SetName(scene->mMeshes[meshIndex]->mName.data);

		printf("\nNode Nro.%d: %s\n", meshIndex, newEntity->GetName());
		printf("Number of children: %d\n", node->mNumChildren);

		Mesh* mesh = new Mesh(newEntity, m_renderer, m_material, m_textureID);
		mesh->ProcessMesh(scene->mMeshes[meshIndex]);
		mesh->GenerateBuffers();
		newEntity->AddComponent(mesh);

		m_entity->AddNode(newEntity);

		meshIndex++;
		for (int nodeIndex = 0; nodeIndex < node->mNumChildren; nodeIndex++) {
			mesh->ProcessNode(node->mChildren[nodeIndex], scene, meshIndex);
		}
	}
}

void Mesh::AttachMeshToEntity(aiMesh* mesh) {
	//Mesh* mesh = new Mesh(entity, m_renderer, m_material, m_textureID);
	ProcessMesh(mesh);
	GenerateBuffers();
}

void Mesh::ProcessMesh(aiMesh* mesh) {
	FillVBOinfo(mesh);
	FillFaceIndices(mesh);
}

void Mesh::FillVBOinfo(aiMesh* mesh) {
	m_indexedVertices.reserve(mesh->mNumVertices);
	m_indexedUVs.reserve(mesh->mNumVertices);
	m_indexedNormals.reserve(mesh->mNumVertices);
	
	//glm::vec3 maxVertex = glm::vec3(-10000.0f, -10000.0f, -10000.0f);
	//glm::vec3 minVertex= glm::vec3(10000.0f, 10000.0f, 10000.0f);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {

		aiVector3D pos = mesh->mVertices[i];
		glm::vec3 vertexToProcess = glm::vec3(pos.x, pos.y, pos.z);
		//GenerateBoundingBoxDimensions(maxVertex, minVertex, vertexToProcess);

		m_indexedVertices.push_back(glm::vec3(pos.x, pos.y, pos.z));

		aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		m_indexedUVs.push_back(glm::vec2(UVW.x, UVW.y));

		aiVector3D n = mesh->mNormals[i];
		m_indexedNormals.push_back(glm::vec3(n.x, n.y, n.z));
	}
	//m_entity->GetTransform()->SetBoundingBoxDimensions(minVertex, maxVertex);
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

void Mesh::GenerateBoundingBoxDimensions(glm::vec3& maxVertex, glm::vec3& minVertex, glm::vec3 vertexToCompare) {
	if (vertexToCompare.x > maxVertex.x) {
		maxVertex.x = vertexToCompare.x;
	}
	if (vertexToCompare.y > maxVertex.y) {
		maxVertex.y = vertexToCompare.y;
	}
	if (vertexToCompare.z > maxVertex.z) {
		maxVertex.z = vertexToCompare.z;
	}

	if (vertexToCompare.x < minVertex.x) {
		minVertex.x = vertexToCompare.x;
	}
	if (vertexToCompare.y < minVertex.y) {
		minVertex.y = vertexToCompare.y;
	} 
	if (vertexToCompare.z < minVertex.z) {
		minVertex.z = vertexToCompare.z;
	}
}

#include "Mesh.h"
#include "OBJ_Loader.h"
#include "TextureLoader.h"
#include "Transform.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

Mesh::Mesh(Renderer* renderer, Material* material, const char* texturePath) : Entity(renderer) {
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
	SceneNode::Update(deltaTime);
}

void Mesh::Draw() {
	m_renderer->UpdateModelMatrix(GetTransform()->GetModelMatrix());
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

bool Mesh::LoadOBJFromFile(const char* filePath) {
	if(!OBJ_Loader::ExtractVertexInfoFromOBJ(
		filePath,
		m_vertices,
		m_uvs,
		m_normals
	)) {
		return false;
	}

	if (!GenerateIndexedVBO(
		m_vertices,
		m_uvs,
		m_normals,

		m_indices,
		m_indexedVertices,
		m_indexedUVs,
		m_indexedNormals
	)) {
		return false;
	}

	return true;
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

bool Mesh::GenerateIndexedVBO(
	vector<glm::vec3>& in_vertices,
	vector<glm::vec2>& in_uvs,
	vector<glm::vec3>& in_normals,

	vector<unsigned short>& out_indices,
	vector<glm::vec3>& out_vertices,
	vector<glm::vec2>& out_uvs,
	vector<glm::vec3>& out_normals) {

	printf("Generating Indexed VBO ");
	std::map<PackedVertex, unsigned short> VertexToOutIndex;

	// For each input vertex
	for (unsigned int i = 0; i < in_vertices.size(); i++) {

		PackedVertex packed = { in_vertices[i], in_uvs[i], in_normals[i] };

		// Try to find a similar vertex in out_XXXX
		unsigned short index;
		bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

		if (found) { // A similar vertex is already in the VBO, use it instead !
			out_indices.push_back(index);
		}
		else { // If not, it needs to be added in the output data.
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			unsigned short newindex = (unsigned short)out_vertices.size() - 1;
			out_indices.push_back(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}
	printf("SUCCESS\n");
	return true;
}

bool Mesh::getSimilarVertexIndex_fast(
	PackedVertex & packed,
	std::map<PackedVertex, unsigned short> & VertexToOutIndex,
	unsigned short & result) {

	std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
	if (it == VertexToOutIndex.end()) {
		return false;
	}
	else {
		result = it->second;
		return true;
	}
}

void Mesh::GenerateBuffers() {

	// Vertices
	m_vertexBuffer = m_renderer->GenBuffer(&m_indexedVertices[0], m_indexedVertices.size() * sizeof(glm::vec3));

	// UVs
	m_uvBuffer = m_renderer->GenBuffer(&m_indexedUVs[0], m_indexedUVs.size() * sizeof(glm::vec2));

	// Normals
	m_normalBuffer = m_renderer->GenBuffer(&m_indexedNormals[0], m_indexedNormals.size() * sizeof(glm::vec3));

	// Indices
	m_elementsBuffer = m_renderer->GenElementsBuffer(&m_indices[0], m_indices.size() * sizeof(unsigned short));
}
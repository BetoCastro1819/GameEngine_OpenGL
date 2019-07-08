#pragma once
#include "Component.h"
#include <vector>
#include <map>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Renderer;
class Material;
class Entity;
class aiMesh;

using namespace std;

class ENGINEDLL_API Mesh : public Component {
private:
	Material* m_material;
	Renderer* m_renderer;
	//vector<Mesh> m_meshes;

	unsigned int m_programID;
	unsigned int m_lightID;
	unsigned int m_textureID;
	const char* m_texturePath;

	unsigned int m_vertexBuffer;
	unsigned int m_uvBuffer;
	unsigned int m_normalBuffer;
	unsigned int m_elementsBuffer;

	vector<unsigned short> m_indices;
	vector<glm::vec3> m_indexedVertices;
	vector<glm::vec2> m_indexedUVs;
	vector<glm::vec3> m_indexedNormals;
	
	bool LoadModelWithAssimp(const char* filePath);
	void SetShader(unsigned int programId);
	void SetTexture(const char* filePath);
	void FillVBOinfo(aiMesh* mesh);
	void FillFaceIndices(aiMesh* mesh);

public:
	Mesh(Entity* entity, Renderer* renderer, Material* material, const char* texturePath);
	~Mesh() { }
	
	void Update(float deltaTime) override;

	bool LoadModel(const char* filePath);
	void ProcessMesh(aiMesh* mesh);
	void GenerateBuffers();
	void Draw();
};
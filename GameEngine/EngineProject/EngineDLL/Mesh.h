#pragma once
#include "Component.h"
#include <vector>
#include <map>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Renderer;
class Material;
class Entity;
struct aiMesh;
struct aiNode;
struct aiScene;

using namespace std;

class ENGINEDLL_API Mesh : public Component {
private:
	Material* m_material;
	Renderer* m_renderer;

	unsigned int m_programID;
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
	void GenerateBoundingBoxDimensions(glm::vec3& maxVertex, glm::vec3& minVertex, glm::vec3 vertexToCompare);

public:
	Mesh(Entity* entity, Renderer* renderer, Material* material, const char* texturePath);
	Mesh(Entity* entity, Renderer* renderer, Material* material, unsigned int textureID);
	~Mesh() { }
	
	void Update(float deltaTime) override;

	bool LoadModel(const char* filePath);
	void ProcessMesh(aiMesh* mesh);
	int ProcessNode(aiNode* node, const aiScene* scene, int& nodeIndex);
	void GenerateBuffers();
	void Draw();
};
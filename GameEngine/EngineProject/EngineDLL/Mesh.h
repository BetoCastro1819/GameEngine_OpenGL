#pragma once
#include "Component.h"
#include <vector>
#include <map>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Renderer;
class Material;
class Entity;

using namespace std;

class ENGINEDLL_API Mesh : public Component {
private:
	Material* m_material;
	Renderer* m_renderer;

	unsigned int m_programID;
	unsigned int m_lightID;
	unsigned int m_textureID;

	unsigned int m_vertexBuffer;
	unsigned int m_uvBuffer;
	unsigned int m_normalBuffer;
	unsigned int m_elementsBuffer;

	vector<unsigned short> m_indices;
	vector<glm::vec3> m_indexedVertices;
	vector<glm::vec2> m_indexedUVs;
	vector<glm::vec3> m_indexedNormals;
	
	void SetShader(unsigned int programId);
	void SetTexture(const char* filePath);

	void GenerateBuffers();
	void Draw();

public:
	Mesh(Entity* entity, Renderer* renderer, Material* material, const char* texturePath);
	~Mesh() {}
	
	void Update(float deltaTime) override;

	bool LoadWithAssimp(const char* filePath);
};
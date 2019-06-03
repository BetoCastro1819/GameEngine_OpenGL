#pragma once
#include "Entity.h"
#include "Material.h"
#include <vector>
#include <map>

class ENGINEDLL_API Mesh : public Entity {
private:
	Material* m_material;

	unsigned int m_programID;
	unsigned int m_lightID;
	unsigned int m_textureID;

	unsigned int m_vertexBuffer;
	unsigned int m_uvBuffer;
	unsigned int m_normalBuffer;
	unsigned int m_elementsBuffer;

	vector<glm::vec3> m_vertices;
	vector<glm::vec2> m_uvs;
	vector<glm::vec3> m_normals;
	
	vector<unsigned short> m_indices;
	vector<glm::vec3> m_indexedVertices;
	vector<glm::vec2> m_indexedUVs;
	vector<glm::vec3> m_indexedNormals;


	void SetShader(unsigned int programId);
	void SetTexture(const char* filePath);


	struct PackedVertex {
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 normal;
		bool operator<(const PackedVertex that) const {
			return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
		};
	};

	void GenerateBuffers();
	bool GenerateIndexedVBO(
		vector<glm::vec3>& in_vertices,
		vector<glm::vec2>& in_uvs,
		vector<glm::vec3>& in_normals,

		vector<unsigned short>& out_indices,
		vector<glm::vec3>& out_vertices,
		vector<glm::vec2>& out_uvs,
		vector<glm::vec3>& out_normals
	);
	bool getSimilarVertexIndex_fast(
		PackedVertex & packed,
		std::map<PackedVertex, unsigned short> & VertexToOutIndex,
		unsigned short & result
	);

	void Draw();

public:
	Mesh(Renderer* renderer, Material* material, const char* texturePath);
	~Mesh() {}
	
	void Update(float deltaTime) override;

	bool LoadOBJFromFile(const char* filePath);
	bool LoadWithAssimp(const char* filePath);
};
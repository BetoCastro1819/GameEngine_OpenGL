#pragma once
#include "Entity.h"
#include "Material.h"
#include <vector>
#include <map>

struct PackedVertex {
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	bool operator<(const PackedVertex that) const {
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
	};
};

class ENGINEDLL_API Mesh : public Entity {
private:
	Renderer* m_renderer;
	Material* m_material;

	unsigned int m_programID;
	unsigned int m_lightID;
	unsigned int m_textureID;
	unsigned int m_texture;

	vector<glm::vec3> m_vertices;
	vector<glm::vec2> m_uvs;
	vector<glm::vec3> m_normals;
	
	vector<unsigned short> m_indices;
	vector<glm::vec3> m_indexedVertices;
	vector<glm::vec2> m_indexedUVs;
	vector<glm::vec3> m_indexedNormals;

	void GenerateBuffers();

public:
	Mesh(Renderer* renderer, Material* material);
	~Mesh();

	void Draw() override;

	void SetTexture(const char* filePath);
	bool LoadOBJFromFile(const char* filePath);
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
};


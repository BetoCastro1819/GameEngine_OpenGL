#pragma once
#include "Entity.h"
#include "Shader.h"

#include <vector>

using namespace std;

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	string type;
};

class ENGINEDLL_API Mesh : public Entity
{
private:
	Renderer* m_Renderer;

	/*  Mesh Data  */
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	

	/*  Render data  */
	unsigned int VAO, VBO, EBO;


public:
	Mesh(Renderer* renderer);

	void SetVertices(const vector<Vertex>& vertices)		{ this->vertices = vertices; }
	void SetIndices(const vector<unsigned int>& indices)	{ this->indices  = indices;  }
	void SetTextures(const vector<Texture>& textures)		{ this->textures = textures; }

	void SetupMesh();

	~Mesh();

	void Draw(Shader shader);
};


#pragma once
#include "Exports.h"
#include "Component.h"
#include "glm/glm.hpp"

class ENGINEDLL_API Material : public Component {
private:
	unsigned int m_ProgramID;
	unsigned int m_MatrixID;
	unsigned int m_TextureID;
	
public:
	Material(Entity* entity);
	~Material();

	void Update(float deltaTime) override { }

	unsigned int GetShaderID() { return m_ProgramID; }
	bool LoadShaders(const char * vertex_file_path, const char * fragment_file_path);	
	unsigned int Load_BMP(const char* imagePath);
	void SetMatrixProperty(const char* name, const glm::mat4& mat);
	void SetTextureProperty(const char* name, unsigned int textureID);
};


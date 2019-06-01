#pragma once
#include "Exports.h"
#include "glm/glm.hpp"

class ENGINEDLL_API Material {
private:
	unsigned int m_ProgramID;
	unsigned int m_MatrixID;
	unsigned int m_TextureID;
	
public:
	Material();
	~Material();

	unsigned int GetShaderID() { return m_ProgramID; }
	bool LoadShaders(const char * vertex_file_path, const char * fragment_file_path);	
	unsigned int Load_BMP(const char* imagePath);
	void SetMatrixProperty(const char* name, const glm::mat4& mat);
	void SetTextureProperty(const char* name, unsigned int textureID);
};


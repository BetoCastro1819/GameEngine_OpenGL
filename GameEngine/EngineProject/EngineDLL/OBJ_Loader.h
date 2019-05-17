#pragma once
#include "Exports.h"
#include "glm/glm.hpp"
#include <vector>

class ENGINEDLL_API OBJ_Loader {
public:
	static bool ExtractVertexInfoFromOBJ(
		const char* filePath,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals
	);

	static bool loadWithAssimp(
		const char* path,
		std::vector<unsigned short>& indices,
		std::vector<glm::vec3>& vertices,
		std::vector<glm::vec2>& uvs,
		std::vector<glm::vec3>& normals
	);
};


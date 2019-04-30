#pragma once
#include "Exports.h"
#include "glm/glm.hpp"
#include <vector>
using namespace std;

class ENGINEDLL_API OBJ_Loader {
public:
	static bool fillVerticesWithOBJInfo(
		const char* filePath,
		vector<glm::vec3>& out_vertices,
		vector<glm::vec2>& out_uvs,
		vector<glm::vec3>& out_normals
	);
};


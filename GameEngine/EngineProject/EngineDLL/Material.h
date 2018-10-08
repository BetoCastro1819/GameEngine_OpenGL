#pragma once
#include "Exports.h"

class ENGINEDLL_API Material {
public:
	Material();
	~Material();
	unsigned int LoadShaders(const char * vertex_file_path, const char * fragment_file_path);	
	unsigned int Load_BMP(const char* imagePath);
};


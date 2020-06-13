#pragma once
#include "Exports.h"

class ENGINEDLL_API TextureLoader {
public:
	static unsigned int LoadFromFile_DDS(const char* filePath);
	static unsigned int LoadFromFile_BMP(const char* filePath);
};


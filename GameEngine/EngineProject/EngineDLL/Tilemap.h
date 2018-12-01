#pragma once
#pragma once
#include "Exports.h"
#include "Renderer.h"

class ENGINEDLL_API Tilemap {
private:
	Renderer* _renderer;

public:
	Tilemap(Renderer* renderer);
	~Tilemap();
	void DrawTilemap();

};


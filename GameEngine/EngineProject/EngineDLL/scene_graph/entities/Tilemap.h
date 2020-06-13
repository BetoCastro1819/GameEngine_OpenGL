#pragma once
#include "../../misc//Exports.h"
#include "Sprite.h"


class Renderer;

class ENGINEDLL_API Tilemap : public Sprite {
private:
	unsigned int _tileVtxCount;
	unsigned int _tileVtxCountUV;
	unsigned int _numCols;
	unsigned int _numRows;
	float _tileWidth;
	float _tileHeight;

public:
	Tilemap(Renderer* renderer,
			unsigned int tileSheetWidth,
			unsigned int tileSheetHeight,
			unsigned int tileWidth,
			unsigned int tileHeight,
			unsigned int numCols,
			unsigned int numRows,
			const char* tilePalletePath);
	
	~Tilemap();
};
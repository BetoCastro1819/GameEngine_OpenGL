#include "Tilemap.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>

Tilemap::Tilemap(
	Renderer*		renderer,
	unsigned int	tileSheetWidth,
	unsigned int	tileSheetHeight,
	unsigned int	tileWidth,
	unsigned int	tileHeight,
	unsigned int	numCols,
	unsigned int	numRows
	)
	: Sprite(
		renderer,
		0,
		tileSheetWidth,
		tileSheetHeight,
		tileWidth,
		tileHeight,
		2,
		2,
		false) 
{
	// Actual code after horrible constructor
	// Initialize private variables
	_tileWidth = tileWidth;
	_tileHeight = tileHeight;
	_numCols = numCols;
	_numRows = numRows;
	_frame.x = 0;
	_frame.y = 0;

	/* GENERATE VERTEX BUFFER */
	_tileVtxCount = 0;

	vector<float> tilemapVtxBuffer;
	
	for (int col = 0; col < numCols; col++) {
		for (int row = 0; row < numRows; row++) {
			// Vertex positions per box on the tilemap grid

			// BOTTOM - LEFT
			tilemapVtxBuffer.push_back(0.0f + row * tileWidth);			// X
			tilemapVtxBuffer.push_back(0.0f + col * tileHeight);			// Y
			tilemapVtxBuffer.push_back(0.0f);								// Z
			_tileVtxCount++;

			// TOP - LEFT
			tilemapVtxBuffer.push_back(0.0f + row * tileWidth);			// X
			tilemapVtxBuffer.push_back(_tileHeight + col * tileHeight);	// Y
			tilemapVtxBuffer.push_back(0.0f);								// Z
			_tileVtxCount++;

			// TOP - RIGHT
			tilemapVtxBuffer.push_back(_tileWidth + row * tileWidth);		// X
			tilemapVtxBuffer.push_back(_tileHeight + col * tileHeight);	// Y
			tilemapVtxBuffer.push_back(0.0f);								// Z
			_tileVtxCount++;

			// BOTTOM - RIGHT
			tilemapVtxBuffer.push_back(_tileWidth + row * tileWidth);		// X
			tilemapVtxBuffer.push_back(0.0f + col * tileHeight);			// Y
			tilemapVtxBuffer.push_back(0.0f);								// Z
			_tileVtxCount++;
		}
	}
	SetVertices(&tilemapVtxBuffer[0], _tileVtxCount);

	/* GENERATE VERTEX UV BUFFER */
	unsigned int gridLevelIndexes[] = {
		1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,
	};

	_tileVtxCountUV = 0;

	vector<float> tilemapVtxBufferUV;
	
	for (int gridPos = 0; gridPos < numCols * numRows; gridPos++) {

		int tileIndex = gridLevelIndexes[gridPos];

		_frame.x = (tileIndex % numRows) * tileWidth;
		_frame.y = (tileIndex / numCols) * tileHeight;

		// V0 = BOTTOM LEFT
		tilemapVtxBufferUV.push_back(_frame.x / tileSheetWidth);
		tilemapVtxBufferUV.push_back(1 - (_frame.y + tileHeight) / tileSheetHeight);
		_tileVtxCountUV++;

		// V1 = TOP LEFT
		tilemapVtxBufferUV.push_back(_frame.x / tileSheetWidth);
		tilemapVtxBufferUV.push_back(1 - (_frame.y / tileSheetHeight));
		_tileVtxCountUV++;
		
		// V2 = TOP RIGHT
		tilemapVtxBufferUV.push_back((_frame.x + tileWidth) / tileSheetWidth);
		tilemapVtxBufferUV.push_back(1 - (_frame.y / tileSheetHeight));
		_tileVtxCountUV++;

		// V3 = BOTTOM RIGHT
		tilemapVtxBufferUV.push_back((_frame.x + tileWidth) / tileSheetWidth);
		tilemapVtxBufferUV.push_back(1 - (_frame.y + tileHeight) / tileSheetHeight);
		_tileVtxCountUV++;
	}
	std::cout << "Number of UV vertices: " << _tileVtxCountUV << std::endl;
	SetUVBufferData(&tilemapVtxBufferUV[0], _tileVtxCountUV);
}


Tilemap::~Tilemap() {
}

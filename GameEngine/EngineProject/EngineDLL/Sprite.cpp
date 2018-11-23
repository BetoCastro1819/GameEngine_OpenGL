#include "Sprite.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>


Sprite::Sprite(
	Renderer* renderer,
	unsigned int frameID,
	unsigned int textureWidth,
	unsigned int textureHeight,
	unsigned int frameWidth,
	unsigned int frameHeight,
	unsigned int numColums,
	unsigned int numRows,
	bool isAnimated
	) : Shape(renderer) {				// Initialize base constructor

	// Initialize variables
	_frameID		= frameID;
	_frame.x		= 0;
	_frame.y		= 0;
	_textureWidth	= textureWidth;
	_textureHeight	= textureHeight;
	_frameWidth		= frameWidth;
	_frameHeight	= frameHeight;
	_numColums		= numColums;
	_numRows		= numRows;


	GLfloat vertexBuffer[] = {
		-1.0f, -1.0f, 0.0f,				// BOTTOM	- LEFT
		-1.0f,  1.0f, 0.0f,				// TOP		- LEFT
		 1.0f, -1.0f, 0.0f,				// BOTTOM	- RIGHT
		 1.0f,  1.0f, 0.0f,				// TOP		- RIGHT
	};


	// 2 UV coordinates for each vertex

	GLfloat UV_Buffer[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
	};


	// If the sprite is animated
	// Set new UV coordinates
	if (isAnimated) {
		//	x = (id % numFramesAncho) * anchoDelFrame;
		//	y = (id / numFramesAlto) * altoDelFrame;

		if (_frameID <= (numRows * numColums) - 1) {
			// Calculate frame coordinates based on ID position on the sprite sheet
			_frame.x = (_frameID % numRows) * frameWidth;
			_frame.y = (_frameID / numColums) * frameHeight;

			// V0 = BOTTOM LEFT
			UV_Buffer[0] = _frame.x / textureWidth;							// U coord
			UV_Buffer[1] = 1 - (_frame.y + frameHeight) / textureHeight;	// V coord

			// V1 = TOP LEFT
			UV_Buffer[2] = _frame.x / textureWidth;							// U coord
			UV_Buffer[3] = 1 - (_frame.y / textureHeight);					// V coord

			// V2 = BOTTOM RIGHT
			UV_Buffer[4] = (_frame.x + frameWidth) / textureWidth;			// U coord
			UV_Buffer[5] = 1 - (_frame.y + frameHeight) / textureHeight;			// V coord

			// V3 = TOP RIGHT
			UV_Buffer[6] = (_frame.x + frameWidth) / textureWidth;			// U coord
			UV_Buffer[7] = 1 - (_frame.y / textureHeight);					// V coord
		}
		else {
			std::cout << "Frame ID selected is out of bounds" << std::endl;
		}
	}


	_texture = _mat->Load_BMP("uvtemplate.bmp");
	_textureID = _renderer->SetTextureID(_programID);

	SetVertices(vertexBuffer, 4);
	SetUVBufferData(UV_Buffer);
}


Sprite::~Sprite() {
	//Dispose();
	_renderer->DeleteBuffers(_uvBufferData);
	_renderer->DeleteTextures(_texture);

	/* TODO: program crashes when it has to delete THESE vertices*/
	if (_uvVrtxs != nullptr) {
		//delete[] _uvVrtxs;
		_uvVrtxs = NULL;
	}

	std::cout << "TextureShape::~TextureShape()" << std::endl;
}

void Sprite::DrawSprite() {
	Draw();
	_renderer->BindTexture(_texture);
	_renderer->SetTextureSampler(_textureID);
	_renderer->BindBuffer(_uvBufferData, _uvVrtxCount, 1, 2, _drawMode);

}

void Sprite::SetUVBufferData(float* vrtxs) {
	_uvVrtxs = vrtxs;
	_uvVrtxCount = 4;
	_uvBufferData = _renderer->GenBuffer(_uvVrtxs, _uvVrtxCount * 2 * sizeof(float));
}

void Sprite::SetFrame(int frameID) {
	_frameID = frameID;

	// Check that ID selected lower than the amount of frames on the spriteSheet
	if (_frameID <= (_numRows * _numColums) - 1) {
		// Calculate frame coordinates based on ID position on the sprite sheet
		_frame.x = (_frameID % _numRows) * _frameWidth;
		_frame.y = (_frameID / _numColums) * _frameHeight;

		float uvCoords[] = 
		{
			// V0 = BOTTOM LEFT
			_frame.x / _textureWidth,
			1 - (_frame.y + _frameHeight) / _textureHeight,

			// V1 = TOP LEFT
			_frame.x / _textureWidth,		
			1 - (_frame.y / _textureHeight),

			// V2 = BOTTOM RIGHT
			(_frame.x + _frameWidth) / _textureWidth,		
			1 - (_frame.y + _frameHeight) / _textureHeight,

			// V3 = TOP RIGHT
			(_frame.x + _frameWidth) / _textureWidth,		
			1 - (_frame.y / _textureHeight)			
		};
		
		SetUVBufferData(uvCoords);
	}
	else {
		std::cout << "Frame ID selected is out of bounds" << std::endl;
	}
}
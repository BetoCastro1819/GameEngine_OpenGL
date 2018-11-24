#pragma once
#include "Exports.h"
#include "Shape.h"
#include "Animation.h"

struct ENGINEDLL_API  FramePos {
	float x;
	float y;
};

class ENGINEDLL_API  Sprite : public Shape {
private:

	float*			_uvVrtxs;						// Pointer to the 1st value of the array of vertices
	int				_uvVrtxCount;					// Number of vertices to draw
	int				_uvBufferData;					// UV Buffer Data generated from the renderer
	unsigned int	_textureID;						// Texture ID that will be passed to the "Texture Sampler" of the renderer
	unsigned int	_texture;						// Actual texture file in BMP format

	/* ANIMATED SPRITE */
	Animation*		_animation;						// Stores and plays sprite's animations
	FramePos		_frame;							// Struct that will store X and Y position of the frame based on it's ID 
	unsigned int	_frameID;						// ID of the frame that will be selected from the sprite sheet to be drawn
	unsigned int	_textureWidth;					// Width of the texture in pixels
	unsigned int	_textureHeight;					// Height of the texture in pixels
	unsigned int	_frameWidth;					// Width of each frame cell from the sprite sheet
	unsigned int	_frameHeight;					// Height of each frame cell from the sprite sheet
	unsigned int	_numColums;						// Max number of frames per columns
	unsigned int	_numRows;						// Max number of frames per rows

public:
	Sprite (
		Renderer*		renderer,					// Pointer to renderer that will draw sprite on screen
		unsigned int	frameID,					// ID of the frame that will be selected from the sprite sheet to be drawn
		unsigned int	textureWidth,				// Width of the texture in pixels
		unsigned int	textureHeight,				// Height of the texture in pixels
		unsigned int	frameWidth,					// Width of each frame cell from the sprite sheet
		unsigned int	frameHeight,				// Height of each frame cell from the sprite sheet
		unsigned int	numColums,					// Number of horizontal frames
		unsigned int	numRows,					// Number of vertical frames
		bool			isAnimated					// Boolean that enables animation on the sprite
	);

	~Sprite();
	void DrawSprite();
	void SetUVBufferData(float* vrtxs);
	void SetFrame(int frameID);

	/* Animated Sprite */
	void AddAnimation(const char* animationName, std::vector<int> animationFrames);
	void PlayAnimation(float deltaTime);
	void SetAnimation(const char* animationName);
};
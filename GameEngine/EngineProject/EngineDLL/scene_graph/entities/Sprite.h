#pragma once
#include "../../misc/Exports.h"
#include "Shape.h"

class Shape;
class Animation;
class Window;
class BoxCollider;

struct ENGINEDLL_API  FramePos {
	float x;
	float y;
};

class ENGINEDLL_API  Sprite : public Shape {
protected:
	float* _uvVrtxs;
	int	_uvVrtxCount;
	int	_uvBufferData;
	unsigned int _textureID;
	unsigned int _texture;

	BoxCollider* _boxCollider;

	Animation* _animation;
	FramePos _frame;
	unsigned int _frameID;						
	unsigned int _textureWidth;					
	unsigned int _textureHeight;				
	unsigned int _frameWidth;					
	unsigned int _frameHeight;					
	unsigned int _numColums;					
	unsigned int _numRows;						

public:
	Sprite (
		Renderer*		renderer,					
		unsigned int	frameID,					
		unsigned int	textureWidth,				
		unsigned int	textureHeight,				
		unsigned int	frameWidth,					
		unsigned int	frameHeight,				
		unsigned int	numColums,					
		unsigned int	numRows,					
		bool			isAnimated,					
		const char*		spritesheetPath				
	);

	~Sprite();
	void DrawSprite();
	void SetUVBufferData(float* vrtxs, int vtxCount);
	void SetFrame(int frameID);

	void InitVertices();
	void InitVerticesUV();

	void AddAnimation(const char* animationName, std::vector<int> animationFrames);
	void PlayAnimation(float deltaTime);
	void SetAnimation(const char* animationName);
	void SetAnimationSpeed(float speed);

	void HandleInput(Window* window, float deltaTime);

	BoxCollider* GetBoxCollider() { return _boxCollider; }
};
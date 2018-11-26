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

	_texture = _mat->Load_BMP("uvtemplate.bmp");
	_textureID = _renderer->SetTextureID(_programID);

	SetVertices(vertexBuffer, 4);
	SetUVBufferData(UV_Buffer);

	// If the sprite is animated
	// Set new UV coordinates
	if (isAnimated) {
		SetFrame(frameID);
	}
	_animation = NULL;


	_boxCollider = new BoxCollider(_frameWidth, _frameHeight);
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

	if (_boxCollider != nullptr) {
		delete _boxCollider;
		_boxCollider = NULL;
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

void Sprite::AddAnimation(const char* animationName, std::vector<int> animationFrames) {

	if (_animation == NULL) {
		_animation = new Animation();
	}
	
	_animation->AddAnimation(animationName, animationFrames);
}

void Sprite::PlayAnimation(float deltaTime) {
	//std::cout << "Animation Frame " << _animation->GetAnimationFrame(deltaTime) << std::endl;
	SetFrame(_animation->GetAnimationFrame(deltaTime));
}

void Sprite::SetAnimation(const char* animationName) {
	if (_animation != NULL) {
		_animation->SetAnimation(animationName);
	}
}

void Sprite::SetAnimationSpeed(float animationSpeed) {
	if (_animation != NULL) {
		_animation->SetAnimationSpeed(animationSpeed);
	}
}

void Sprite::HandleInput(Window* window, float deltaTime) {
	float speed = 250.0f * deltaTime;

	glm::vec3 position = GetPos();
	// Move forward
	if (glfwGetKey((GLFWwindow*)window->GetWindowPtr(), GLFW_KEY_UP) == GLFW_PRESS) {
		SetPos(position.x, position.y + speed, position.z);
	}
	// Move backward
	if (glfwGetKey((GLFWwindow*)window->GetWindowPtr(), GLFW_KEY_DOWN) == GLFW_PRESS) {
		SetPos(position.x, position.y - speed, position.z);
	}
	// Strafe right
	if (glfwGetKey((GLFWwindow*)window->GetWindowPtr(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		SetPos(position.x + speed, position.y, position.z);
	}
	// Strafe left
	if (glfwGetKey((GLFWwindow*)window->GetWindowPtr(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		SetPos(position.x - speed, position.y, position.z);
	}
	
}
#include "Sprite.h"
//#include "Entity.h"

#include "../../components/Transform.h"

#include "../../components/Animation.h"
#include "../../core/Window.h"
#include "../../components/BoxCollider.h"

#include "../../components/Material.h"
#include "../../rendering/Renderer.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

Sprite::Sprite(Renderer* renderer,
			   unsigned int frameID,
			   unsigned int textureWidth,
			   unsigned int textureHeight,
			   unsigned int frameWidth,
			   unsigned int frameHeight,
			   unsigned int numColums,
			   unsigned int numRows,
			   bool isAnimated,
			   const char* spritesheetPath) 
	: Shape(renderer) {
	
	_frameID		= frameID;
	_frame.x		= 0;
	_frame.y		= 0;
	_textureWidth	= textureWidth;
	_textureHeight	= textureHeight;
	_frameWidth		= frameWidth;
	_frameHeight	= frameHeight;
	_numColums		= numColums;
	_numRows		= numRows;

	_texture = _mat->Load_BMP(spritesheetPath);
	_textureID = m_renderer->SetTextureID(_programID);

	
	if (isAnimated) {
		SetFrame(frameID);
	}
	_animation = NULL;

	_boxCollider = new BoxCollider(_frameWidth, _frameHeight);

	std::cout << "Sprite::Sprite()" << std::endl;
}


Sprite::~Sprite() {
	//Dispose();
	m_renderer->DeleteBuffers(_uvBufferData);
	m_renderer->DeleteTextures(_texture);

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
	//Draw();

	if (_mat) {
		BindMaterial();

		// Set matrix property
		_mat->SetMatrixProperty("MVP", m_renderer->GetMVP());

		// Set texture property
		_mat->SetTextureProperty("myTextureSampler", _texture);
	}

	// Bind Vertex Buffer (Attribute index = 0)
	m_renderer->BindBuffer(_bufferData, _vrtxCount, 0, 3, _drawMode);

	m_renderer->BindTexture(_texture);
	m_renderer->SetTextureSampler(_textureID);
	m_renderer->BindBuffer(_uvBufferData, _uvVrtxCount, 1, 2, _drawMode);

	m_renderer->UpdateModelMatrix(GetTransform()->GetWorldMatrix());
	m_renderer->UpdateMVP();
	//_renderer->SendTransformationToShader(_matrixID);
}

void Sprite::SetUVBufferData(float* vrtxs, int vtxCount) {
	_uvVrtxs = vrtxs;
	_uvVrtxCount = vtxCount;
	_uvBufferData = m_renderer->GenBuffer(_uvVrtxs, _uvVrtxCount * 2 * sizeof(float));
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
		
		SetUVBufferData(uvCoords, 4);
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

	glm::vec3 position = GetTransform()->GetPosition();
	// Move forward
	if (glfwGetKey((GLFWwindow*)window->GetWindowPtr(), GLFW_KEY_UP) == GLFW_PRESS) {
		GetTransform()->SetPosition(position.x, position.y + speed, position.z);
	}
	// Move backward
	if (glfwGetKey((GLFWwindow*)window->GetWindowPtr(), GLFW_KEY_DOWN) == GLFW_PRESS) {
		GetTransform()->SetPosition(position.x, position.y - speed, position.z);
	}
	// Strafe right
	if (glfwGetKey((GLFWwindow*)window->GetWindowPtr(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		GetTransform()->SetPosition(position.x + speed, position.y, position.z);
	}
	// Strafe left
	if (glfwGetKey((GLFWwindow*)window->GetWindowPtr(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		GetTransform()->SetPosition(position.x - speed, position.y, position.z);
	}
}

void Sprite::InitVertices() {

	float halfWidth = _frameWidth / 2;
	float halfHeight = _frameHeight / 2;

	GLfloat vertexBuffer[] = {
		-halfWidth, -halfHeight, 0.0f,				// BOTTOM	- LEFT
		-halfWidth,  halfHeight, 0.0f,				// TOP		- LEFT
		 halfWidth, -halfHeight, 0.0f,				// BOTTOM	- RIGHT
		 halfWidth,  halfHeight, 0.0f,				// TOP		- RIGHT
	};

	SetVertices(vertexBuffer, 4);
}

void Sprite::InitVerticesUV() {
	// 2 UV coordinates for each vertex
	GLfloat UV_Buffer[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
	};

	SetUVBufferData(UV_Buffer, 4);
}
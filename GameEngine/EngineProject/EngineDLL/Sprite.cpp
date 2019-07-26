#include "Sprite.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

Sprite::Sprite(Renderer* renderer, Material* material, Texture* texture) : Shape(renderer) {
	SetMaterial(material);
	SetTexture(texture);

	m_animation = nullptr;

	InitVertices();
}

void Sprite::InitVertices() {

	float halfWidth = m_frameWidth / 2;
	float halfHeight = m_frameHeight / 2;

	GLfloat vertexBuffer[] = {
		-halfWidth, -halfHeight, 0.0f,				// BOTTOM	- LEFT
		-halfWidth,  halfHeight, 0.0f,				// TOP		- LEFT
		 halfWidth, -halfHeight, 0.0f,				// BOTTOM	- RIGHT
		 halfWidth,  halfHeight, 0.0f,				// TOP		- RIGHT
	};
	SetVertices(vertexBuffer, 4);
	InitVerticesUV();
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

Sprite::~Sprite() {
	m_renderer->DeleteBuffers(m_uvBuffer);
	m_renderer->DeleteTextures(m_texture->GetTextureID());

	if (m_uvVertices != nullptr) {
		m_uvVertices = NULL;
	}

	std::cout << "TextureShape::~TextureShape()" << std::endl;
}

void Sprite::SetMaterial(Material* material) {
	m_material = material;
	m_programID = m_material->LoadShaders("SimpleVertexShader.txt", "SimpleFragmentShader.txt");
}

void Sprite::SetTexture(Texture* texture) {
	m_texture = texture;
	m_textureID = texture->GetTextureID();

	printf("Sprite textureID: %d\n", m_textureID);

	m_frameWidth = m_texture->GetFrameWidth();
	m_frameHeight = m_texture->GetFrameHeight();
}

void Sprite::Update(float deltaTime) {
	m_renderer->UpdateModelMatrix(m_ModelMat);
	m_renderer->UpdateMVP();

	BindMaterial();
	
	m_material->SetMatrixProperty("MVP", m_renderer->GetMVP());

	m_renderer->BindTexture(m_textureID);
	m_material->SetTextureProperty("myTextureSampler", m_textureID);

	m_renderer->EnableVertexAttribArray(0);
	m_renderer->BindBuffer(m_vertexBuffer);
	m_renderer->VertexAttribPointer(0, 3);

	m_renderer->EnableVertexAttribArray(1);
	m_renderer->BindBuffer(m_uvBuffer);
	m_renderer->VertexAttribPointer(1, 2);

	m_renderer->DrawArrays(1, m_numberOfVertices);

	m_renderer->DisableVertexArray(0);
	m_renderer->DisableVertexArray(1);
}

void Sprite::SetFrameID(int frameID) {
	m_frameID = frameID;

	int framesPerColumn = m_texture->GetFramesPerColumn();
	int framesPerRow = m_texture->GetFramesPerRow();

	int textureWidth = m_texture->GetWidth();
	int textureHeight = m_texture->GetHeight();


	// Check that ID selected lower than the amount of frames on the spriteSheet
	if (m_frameID <= (framesPerColumn * framesPerRow) - 1) {
		// Calculate frame coordinates based on ID position on the sprite sheet
		m_frame.x = (m_frameID % framesPerColumn) * m_frameWidth;
		m_frame.y = (m_frameID / framesPerRow) * m_frameHeight;

		float uvCoords[] = 
		{
			// V0 = BOTTOM LEFT
			m_frame.x / textureWidth,
			1 - (m_frame.y + m_frameHeight) / textureHeight,

			// V1 = TOP LEFT
			m_frame.x / textureWidth,		
			1 - (m_frame.y / textureHeight),

			// V2 = BOTTOM RIGHT
			(m_frame.x + m_frameWidth) / textureWidth,		
			1 - (m_frame.y + m_frameHeight) / textureHeight,

			// V3 = TOP RIGHT
			(m_frame.x + m_frameWidth) / textureWidth,		
			1 - (m_frame.y / textureHeight)			
		};
		
		SetUVBufferData(uvCoords, 4);
	}
	else {
		std::cout << "Frame ID selected is out of bounds" << std::endl;
	}
}

void Sprite::AddAnimation(const char* animationName, std::vector<int> animationFrames) {

	if (m_animation == nullptr) {
		m_animation = new Animation();
	}
	
	m_animation->AddAnimation(animationName, animationFrames);
}

void Sprite::PlayAnimation(float deltaTime) {
	//std::cout << "Animation Frame " << _animation->GetAnimationFrame(deltaTime) << std::endl;
	SetFrameID(m_animation->GetAnimationFrame(deltaTime));
}

void Sprite::SetAnimation(const char* animationName) {
	if (m_animation != nullptr) {
		m_animation->SetAnimation(animationName);
	}
}

void Sprite::SetAnimationSpeed(float animationSpeed) {
	if (m_animation != nullptr) {
		m_animation->SetAnimationSpeed(animationSpeed);
	}
}

void Sprite::SetUVBufferData(float* vrtxs, int vtxCount) {
	m_uvVertices = vrtxs;
	m_uvVerticesCount = vtxCount;
	m_uvBuffer = m_renderer->GenBuffer(m_uvVertices, m_uvVerticesCount * 2 * sizeof(float));
}
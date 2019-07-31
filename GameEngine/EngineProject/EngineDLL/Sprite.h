#pragma once
#include "Exports.h"
#include "Shape.h"
#include "Animation.h"
#include "BoxCollider.h"
#include "Texture.h"

class ENGINEDLL_API  Sprite : public Shape {
private:
	struct FramePos {
		float x;
		float y;
	};
	FramePos m_frame;
	Animation* m_animation;
	Texture* m_texture;

	unsigned int m_uvBuffer;
	float* m_uvVertices;						
	int m_uvVerticesCount;					
	
	unsigned int m_textureID;
	unsigned int m_frameID;

	int m_frameWidth;
	int m_frameHeight;

	void InitVertices();
	void InitVerticesUV();

public:
	Sprite (Renderer* renderer, Material* material, Texture* texture);
	~Sprite();
	
	void Update(float deltaTime) override;

	void SetMaterial(Material* material) override;

	void SetTexture(Texture* texture);
	void SetFrameID(int frameID);

	void SetUVBufferData(float* vrtxs, int vtxCount);

	void AddAnimation(const char* animationName, std::vector<int> animationFrames);
	void PlayAnimation(const char* animationName, float deltaTime);
	void SetAnimation(const char* animationName);
	void SetAnimationSpeed(float speed);

	void SetModelMatrix(glm::mat4 modelMat) { m_ModelMat = modelMat; }
};
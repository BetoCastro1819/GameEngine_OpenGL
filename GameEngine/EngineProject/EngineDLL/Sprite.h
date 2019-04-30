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
	BoxCollider* m_boxCollider;
	Texture* m_texture;

	float* m_uvVertices;						
	int m_uvVerticesCount;					
	int m_uvBuffer;					
	
	unsigned int m_textureID;
	unsigned int m_frameID;

	int m_frameWidth;
	int m_frameHeight;

	void InitVerticesUV();

public:
	Sprite (Renderer* renderer);
	~Sprite();
	
	void Draw() override;

	void SetMaterial(Material* material) override;

	void SetBoxCollider();
	void SetBoxCollider(unsigned int width, unsigned int height);

	void SetTexture(Texture* texture);
	void SetFrameID(int frameID);


	void InitVertices();
	void SetUVBufferData(float* vrtxs, int vtxCount);

	void AddAnimation(const char* animationName, std::vector<int> animationFrames);
	void PlayAnimation(float deltaTime);
	void SetAnimation(const char* animationName);
	void SetAnimationSpeed(float speed);

	void HandleInput(Window* window, float deltaTime);

	BoxCollider* GetBoxCollider() { return m_boxCollider; }
};
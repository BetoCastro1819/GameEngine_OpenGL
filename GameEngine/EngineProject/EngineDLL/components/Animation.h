#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "../misc/Exports.h"

class ENGINEDLL_API Animation {
private:
	std::map<const char*, std::vector<int>> animations;
	const char* currentAnimation;
	int currentFrameIndex;
	float animationSpeed;
	float animationTimer;

public:
	Animation();
	~Animation();

	void AddAnimation(const char* animationName, std::vector<int> animatedFrames);
	void SetAnimation(const char* animationName);
	const char* GetAnimationName();
	int GetAnimationFrame(float deltaTime);
	void SetAnimationSpeed(float speed);
};


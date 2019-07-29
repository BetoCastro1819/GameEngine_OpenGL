#include "Animation.h"


Animation::Animation() {
	currentAnimation = NULL;
	currentFrameIndex = 0;
	animationTimer = 0;

	// 12 fps as default animation speed
	animationSpeed = 12;
}

Animation::~Animation() {
}

void Animation::AddAnimation(const char* animationName, std::vector<int> animatedFrames) {

	animations.insert(std::pair<const char*, std::vector<int>>(animationName, animatedFrames));
}

void Animation::SetAnimation(const char* animationName) {
	if (animationName != currentAnimation) {
		currentAnimation = animationName;
		currentFrameIndex = 0;
	}
}

const char* Animation::GetAnimationName() {
	return currentAnimation;
}

int Animation::GetAnimationFrame(float deltaTime) {

	if (currentAnimation != NULL) {

		if (animationTimer >= 1.0f / animationSpeed) {

			if (currentFrameIndex + 1 < animations.at(currentAnimation).size() - 1)
				currentFrameIndex++;
			else
				currentFrameIndex = 0;

			animationTimer = 0;
		}
		else {
			animationTimer += deltaTime;
		}
	}

	return animations.at(currentAnimation)[currentFrameIndex];
}

void Animation::SetAnimationSpeed(float speed) {
	animationSpeed = speed;
}

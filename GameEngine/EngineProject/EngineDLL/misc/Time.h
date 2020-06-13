#pragma once
#include "Exports.h"
#include "Shape.h"

class ENGINEDLL_API Time {
private:
	float deltaTime;
	float lastTime;

public:
	void UpdateTime();
	float GetDeltaTime() { return deltaTime; }
	Time();
	~Time();
};


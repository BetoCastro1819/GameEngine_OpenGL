#pragma once
#include "Exports.h"

class ENGINEDLL_API Time {
private:
	float m_deltaTime;
	float m_lastTime;

public:
	Time();
	~Time();

	void UpdateTime();
	float GetDeltaTime();
};


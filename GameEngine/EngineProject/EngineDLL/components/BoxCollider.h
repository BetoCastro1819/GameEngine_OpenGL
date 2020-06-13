#pragma once
#include "../misc/Exports.h"
//#include "Shape.h"
//#include "Animation.h"
//#include "Window.h"

enum CollisionDir {
	LEFT, 
	RIGHT,
	UP,
	DOWN
};

class ENGINEDLL_API BoxCollider {
private:
	double m_boxWidth;
	double m_boxHeight;

public:
	BoxCollider(double boxWidth, double boxHeight);
	~BoxCollider();

	double GetBoxWidth() { return m_boxWidth; }
	void SetBoxWidth(double width) { m_boxWidth = width; }

	double GetBoxHeight() { return m_boxHeight; }
	void SetBoxHeight(double height) { m_boxHeight = height; }
};



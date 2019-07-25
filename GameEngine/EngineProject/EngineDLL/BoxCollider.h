#pragma once
#include "Exports.h"

class ENGINEDLL_API BoxCollider {
private:
	double _boxWidth;
	double _boxHeight;

public:
	BoxCollider(double boxWidth, double boxHeight);
	~BoxCollider();

	double GetBoxWidth() { return _boxWidth; }
	void SetBoxWidth(double width) { _boxWidth = width; }

	double GetBoxHeight() { return _boxHeight; }
	void SetBoxHeight(double height) { _boxHeight = height; }
};



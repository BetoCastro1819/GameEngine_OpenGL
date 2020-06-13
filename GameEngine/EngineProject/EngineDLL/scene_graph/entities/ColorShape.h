#pragma once
#include "../../misc/Exports.h"
#include "Shape.h"

class Renderer;

class ENGINEDLL_API ColorShape : public Shape {
public:
	ColorShape(Renderer* renderer);
	~ColorShape();
};


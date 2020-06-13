#pragma once
#include "Shape.h"

class Renderer;

class ENGINEDLL_API Triangle : public Shape {
public:
	Triangle(Renderer* renderer);
	~Triangle();		
};


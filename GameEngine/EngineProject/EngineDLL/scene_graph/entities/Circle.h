#pragma once
#include <vector>

#include "Shape.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class ENGINEDLL_API Circle : public Shape {
public:
	Circle(Renderer* renderer, double radius, int sides);
	~Circle();
};
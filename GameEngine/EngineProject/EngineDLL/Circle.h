#pragma once
#include "Shape.h"
// GLM -> math library
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

class ENGINEDLL_API Circle : public Shape {
public:
	Circle(Renderer* renderer, double radius, int sides);
	~Circle();
};
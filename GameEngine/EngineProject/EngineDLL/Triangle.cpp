#include "Triangle.h"

Triangle::Triangle(Renderer* renderer) : Shape(renderer) {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	float colorData[] = {
		0.5f,  0.0f,  0.0f,
		0.5f,  0.0f,  0.0f,
		0.5f,  0.0f,  0.0f,
	};

	SetVertices(vertices, 3);
	SetColorBufferData(colorData, 3);

	_dispose = false;
}

Triangle::~Triangle() {
	Dispose();
}
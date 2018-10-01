#include "Triangle.h"

Triangle::Triangle(Renderer* renderer) : Shape(renderer) {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	float colorData[] = {
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
	};

	SetVertices(vertices, 3);
	SetColorBufferData(colorData, 3);

	_dispose = false;
}

Triangle::~Triangle() {
	Dispose();
}
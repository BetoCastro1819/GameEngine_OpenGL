#include "Circle.h"

Circle::Circle(Renderer* renderer, double radius, int sides) : Shape(renderer) {
	std::vector<float> vertices;
	std::vector<float> colorData;
	int vrtxCount = 0;
	
	// Creates vertices to complete circle based on number of sides
	for (int a = 0; a < 360; a += 360 / sides) {
		double path = a * 3.1415926535897932384626433832795 / 180;


		vertices.push_back(cos(path) * radius);	// Vector position in X
		vertices.push_back(sin(path) * radius);	// Vector position in Y
		vertices.push_back(0);					// Vector position in Z

		colorData.push_back(1.0f);	// R
		colorData.push_back(0.0f);	// G
		colorData.push_back(0.0f);	// B

		vrtxCount++; // Number of vertices needed to generate circle
	}

	SetVertices(&vertices[0], vrtxCount);
	SetColorBufferData(&colorData[0], vrtxCount);

	_dispose = false;
}

Circle::~Circle() { }
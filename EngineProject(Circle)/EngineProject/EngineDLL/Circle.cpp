#include "Circle.h"

Circle::Circle(Renderer* renderer, double radius, int sides) : Shape(renderer) {
	// Create the circle in the coordinates origin
	//const int sides = 20;  // The amount of segment to create the circle
	//const double radius = 5; // The radius of the circle

	std::vector<float> vertices;
	std::vector<float> colorData;
	int vrtxCount = 0;
	for (int a = 0; a < 360; a += 360 / sides) {
		double heading = a * 3.1415926535897932384626433832795 / 180;

		vertices.push_back(cos(heading) * radius);
		vertices.push_back(sin(heading) * radius);
		vertices.push_back(0);

		colorData.push_back(1.0f);
		colorData.push_back(0.0f);
		colorData.push_back(0.0f);

		vrtxCount++;
	}

	SetVertices(&vertices[0], vrtxCount);
	SetColorBufferData(&colorData[0], vrtxCount);

	_dispose = false;
}

Circle::~Circle() {
}

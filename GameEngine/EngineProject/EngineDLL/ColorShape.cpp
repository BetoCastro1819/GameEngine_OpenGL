#include "ColorShape.h"

ColorShape::ColorShape(Renderer* renderer):Shape(renderer) {
	m_Renderer->UpdateModelMatrix(m_ModelMat);

	float vertices[] = {
		// Cube using GL_TRIANGLE_STRIP
		/*
		-1.f, 1.f, 1.f,     // Front-top-left
		1.f, 1.f, 1.f,      // Front-top-right
		-1.f, -1.f, 1.f,    // Front-bottom-left
		1.f, -1.f, 1.f,     // Front-bottom-right
		1.f, -1.f, -1.f,    // Back-bottom-right
		1.f, 1.f, 1.f,      // Front-top-right
		1.f, 1.f, -1.f,     // Back-top-right
		-1.f, 1.f, 1.f,     // Front-top-left
		-1.f, 1.f, -1.f,    // Back-top-left
		-1.f, -1.f, 1.f,    // Front-bottom-left
		-1.f, -1.f, -1.f,   // Back-bottom-left
		1.f, -1.f, -1.f,    // Back-bottom-right
		-1.f, 1.f, -1.f,    // Back-top-left
		1.f, 1.f, -1.f      // Back-top-right
		*/

		// Cube using GL_TRIANGLE
		// FRONT FACE
		// 1st Triangle
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 1.0f,
		// 2nd Triangle
		-1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,

		// BACK FACE
		// 1st Triangle
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		// 2nd Triangle
		-1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,

		// LEFT FACE
		// 1st Triangle
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		// 2nd Triangle
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,

		// RIGHT FACE
		// 1st Triangle
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		// 2nd Triangle
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		
		// TOP FACE
		// 1st Triangle
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		// 2nd Triangle
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,

		// BOTTOM FACE
		// 1st Triangle
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		// 2nd Triangle
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
	};

	float colorData[] = {
		/*
		1.0f, 0.0f, 0.0f,	// RED
		0.0f, 1.0f, 0.0f,	// GREEN
		0.0f, 0.0f, 1.0f,	// BLUE
		1.0f, 1.0f, 1.0f,	// WHITE
		1.0f, 0.0f, 0.0f,	// RED
		0.0f, 1.0f, 0.0f,	// GREEN
		0.0f, 0.0f, 1.0f,	// BLUE
		1.0f, 1.0f, 1.0f,	// WHITE
		1.0f, 0.0f, 0.0f,	// RED
		0.0f, 1.0f, 0.0f,	// GREEN
		0.0f, 0.0f, 1.0f,	// BLUE
		1.0f, 1.0f, 1.0f,	// WHITE
		0.0f, 1.0f, 0.0f,	// GREEN
		1.0f, 0.0f, 0.0f,	// RED
		*/
		// FRONT FACE
		// 1st Triangle
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		// 2nd Triangle
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,

		// BACK FACE
		// 1st Triangle
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		// 2nd Triangle
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,

		// LEFT FACE
		// 1st Triangle
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		// 2nd Triangle
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,

		// 1st Triangle
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		// 2nd Triangle
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,

		// TOP FACE
		// 1st Triangle
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		// 2nd Triangle
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,

		// BOTTOM FACE
		// 1st Triangle
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		// 2nd Triangle
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
	};


	// if using GL_TRIANGLE_STRIP = 14 vertices
	// if using GL_TRIANGLE = 6 vertices per face (6 faces in a cube)
	SetVertices(vertices, 6 * 6); // 4 vertices per face, 6 faces in a cube
	SetColorBufferData(colorData, 6 * 6);

	m_Dispose = false;
	m_Renderer->UpdateMVP();
}


ColorShape::~ColorShape() {
}

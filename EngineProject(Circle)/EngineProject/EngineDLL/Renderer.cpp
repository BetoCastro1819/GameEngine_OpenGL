#include "Renderer.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

Renderer::Renderer(Window* window) {	
	_window = window;

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	//_projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	// Uncomment to use orthographic camera
	_projection = glm::ortho(-1.0f,1.0f,-1.0f,1.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	_view = glm::lookAt(
		glm::vec3(0, 0, 2), // Camera is at (0,0,-4), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	LoadIdentityMatrix();
}

Renderer::~Renderer() {
}

bool Renderer::Start() {
	cout << "Renderer::Start()" << endl;
	if (_window) {
		glfwMakeContextCurrent((GLFWwindow*)_window->GetWindowPtr());		
		if (glewInit() == GLEW_OK) {
			glGenVertexArrays(1, (&_vrtxArrID));
			glBindVertexArray(_vrtxArrID);
			return true;
		}
	}
	return false;
}

bool Renderer::Stop() {
	cout << "Renderer::Stop()" << endl;
	return true;
}

void Renderer::SetClearColor(const float& r, const float& g, const float& b, const float& a) {
	glClearColor(r, g, b, a);
}

void Renderer::ClearBuffer() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::RecalculateFragmentDepth() {
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
}

void Renderer::SwapBuffers()  {
	glfwSwapBuffers((GLFWwindow*)_window->GetWindowPtr());
}

unsigned int Renderer::GenBuffer(float* buffer, int size) {
	unsigned int vrtxBuffer;

	glGenBuffers(1, &vrtxBuffer);									// Generates buffer using vrtxBuffer
	glBindBuffer(GL_ARRAY_BUFFER, vrtxBuffer);						// Bind openGL with vrtxBuffer
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);	// OpenGL recieves buffer data
	
	return vrtxBuffer;
}

void Renderer::BindBuffer(unsigned int bufferID, int vtxCount, int attribID) {
	glEnableVertexAttribArray(attribID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	// Structure of shader data
	glVertexAttribPointer(
		attribID,           // Atributte ID. 0 = vertexAttribute | 1 = colorAttribute
		3,                  // SIZE
		GL_FLOAT,           // TYPE
		GL_FALSE,           // NORMALIZED
		0,                  // STRIDE = "pass"
		(void*)0            // ARRAY BUFFER OFFSET
	);

	// DRAW
	// Starts from index 0, up to "vrtxCount" (vrtxCount = 3 -> triangle)
	glDrawArrays(GL_TRIANGLE_FAN, 0, vtxCount);
	glDisableVertexAttribArray(0);
}

void Renderer::DeleteBuffers(unsigned int _buffer) {
	glDeleteBuffers(1, &_buffer);
}

void Renderer::BindMaterial(unsigned int programID) {
	glUseProgram(programID);
}

void Renderer::LoadIdentityMatrix() {
	_model = glm::mat4(1.0f);
}

void Renderer::UpdateModelMatrix(glm::mat4 matrix) {
	_model = matrix;
}

void Renderer::MultiplyModelMatrix(glm::mat4 matrix) {
	//To multiply model's matrix, with parent's model matrix
}

void Renderer::UpdateMVP() {
	// Our ModelViewProjection : multiplication of our 3 matrices
	MVP = _projection * _view * _model; // Matrix multiplication reads from right to left
}

unsigned int Renderer::SetMatrixID(unsigned int programID) {
	return glGetUniformLocation(programID, "MVP");
}

void Renderer::SendTransformationToShader(unsigned int matrixID) {
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
}

void Renderer::DrawCircle(float x, float y, float z, float radius, int numberOfSides) {
	const int numberOfVertices = 5;
	//numberOfSides + 2;

	GLfloat twicePi = 2.0f * 3.14f; // M_PI;

	GLfloat circleVerticesX[numberOfVertices];
	GLfloat circleVerticesY[numberOfVertices];
	GLfloat circleVerticesZ[numberOfVertices];

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for (int i = 1; i < numberOfVertices; i++)
	{
		circleVerticesX[i] = x + (radius * cos(i *  twicePi / numberOfSides));
		circleVerticesY[i] = y + (radius * sin(i * twicePi / numberOfSides));
		circleVerticesZ[i] = z;
	}

	GLfloat allCircleVertices[(numberOfVertices) * 3];

	for (int i = 0; i < numberOfVertices; i++)
	{
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
	glDisableClientState(GL_VERTEX_ARRAY);
}
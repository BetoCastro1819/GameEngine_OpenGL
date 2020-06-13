#include "Renderer.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

Renderer::Renderer(Window* window) {	
	_window = window;
	
	_projection = glm::perspective(
		glm::radians(45.0f),
		(float)window->GetWidth() / (float)window->GetHeight(),
		0.1f,
		100.0f
	);

	//switch (camType) {
	//case CameraType::PERSPECTIVE:
	//	_projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	//	break;
	//case CameraType::ORTHOGRAPHIC:
	//	// Orthographic camera in world coordinates
	//	_projection = glm::ortho(
	//		0.0f,								// LEFT
	//		(float)_window->GetWidth(),			// RIGHT
	//		0.0f,								// BOTTOM
	//		(float)_window->GetHeight(),		// TOP
	//		0.0f,								// zNear
	//		100.0f								// zFar
	//	);
	//	break;
	//}

	// Camera matrix
	_view = glm::lookAt(
		glm::vec3(0, 0, -5),
		glm::vec3(0, 0, 0),	// Look at origin by default
		glm::vec3(0, 1, 0)
	);

	LoadIdentityMatrix();
}

Renderer::~Renderer() {
}

bool Renderer::Start() {
	printf("Starting Renderer ");
	if (_window) {
		glfwMakeContextCurrent((GLFWwindow*)_window->GetWindowPtr());		
		if (glewInit() == GLEW_OK) {
			glGenVertexArrays(1, (&_vrtxArrID));
			glBindVertexArray(_vrtxArrID);
			printf("SUCCESS\n");
			return true;
		}
	}
	printf("ERROR\n");
	return false;
}

bool Renderer::Stop() {
	printf("Stoping Renderer\n");
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

unsigned int Renderer::GenBuffer(glm::vec3* buffer, int size) {
	unsigned int vrtxBuffer;

	glGenBuffers(1, &vrtxBuffer);									// Generates buffer using vrtxBuffer
	glBindBuffer(GL_ARRAY_BUFFER, vrtxBuffer);						// Bind openGL with vrtxBuffer
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);	// OpenGL recieves buffer data

	return vrtxBuffer;
}

unsigned int Renderer::GenBuffer(glm::vec2* buffer, int size) {
	unsigned int vrtxBuffer;

	glGenBuffers(1, &vrtxBuffer);									// Generates buffer using vrtxBuffer
	glBindBuffer(GL_ARRAY_BUFFER, vrtxBuffer);						// Bind openGL with vrtxBuffer
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);	// OpenGL recieves buffer data

	return vrtxBuffer;
}

unsigned int Renderer::GenElementsBuffer(unsigned short* buffer, int size) {
	unsigned int vrtxBuffer;

	glGenBuffers(1, &vrtxBuffer);									// Generates buffer using vrtxBuffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vrtxBuffer);						// Bind openGL with vrtxBuffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);	// OpenGL recieves buffer data

	return vrtxBuffer;
}

void Renderer::BindBuffer(unsigned int bufferID, int vtxCount, int attribID, int size, int drawMode) {
	glEnableVertexAttribArray(attribID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	// Structure of shader data
	glVertexAttribPointer(
		attribID,           // Atributte ID. 0 = vertexAttribute | 1 = colorAttribute
		size,               // SIZE -> 3 for triangles - 2 for UVs
		GL_FLOAT,           // TYPE
		GL_FALSE,           // NORMALIZED
		0,                  // STRIDE = "pass"
		(void*)0            // ARRAY BUFFER OFFSET
	);

	// DRAW
	// Starts from index 0, up to "vrtxCount" (vrtxCount = 3 -> triangle)
	switch (drawMode)
	{
	case 0:
		glDrawArrays(GL_TRIANGLES, 0, vtxCount);
		break;
	case 1:
		glDrawArrays(GL_TRIANGLE_STRIP, 0, vtxCount);
		break;
	case 2:
		glDrawArrays(GL_TRIANGLE_FAN, 0, vtxCount);
		break;
	case 3:
		glDrawArrays(GL_QUADS, 0, vtxCount);
		break;
	case 4: 
		glDrawArrays(GL_LINE, 0, vtxCount);
		break;
	}
	glDisableVertexAttribArray(0);
}

void Renderer::EnableBuffer(int attribID) {
	glEnableVertexAttribArray(attribID);
}

void Renderer::BindBuffer(unsigned int bufferID) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void Renderer::BindElementBuffer(unsigned int bufferID) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
}
void Renderer::SetShaderData(int attribID, int size) {
	glVertexAttribPointer(
		attribID,           // Atributte ID. 0 = vertexAttribute | 1 = colorAttribute
		size,               // SIZE -> 3 for triangles - 2 for UVs
		GL_FLOAT,           // TYPE
		GL_FALSE,           // NORMALIZED
		0,                  // STRIDE = "pass"
		(void*)0            // ARRAY BUFFER OFFSET
	);
}

void Renderer::DrawElements(int numberOfElements) {
	glDrawElements(
		GL_TRIANGLES,			// mode
		numberOfElements,		// count
		GL_UNSIGNED_SHORT,		// type
		(void*)0				// element array buffer offset
	);
}

void Renderer::DisableVertexArrays(int arrayID) {
	glDisableVertexAttribArray(arrayID);
}

void Renderer::BindMaterial(unsigned int programID) {
	glUseProgram(programID);
}

void Renderer::DrawCube(vector<glm::vec3> vertices) {
	glLineWidth(2);

	//	0 - point_frontLowerLeft = origin;
	//	1 - point_frontLowerRight = origin + width;
	//	2 - point_frontUpperRight = origin + width + height;
	//	3 - point_frontUpperLeft = origin + height;
	//	
	//	4 - point_backLowerLeft = origin + length;
	//	5 - point_backLowerRight = origin + width + length;
	//	6 - point_backUpperRight = origin + width + height + length;
	//	7 - point_backUpperLeft = origin + height + length;


	// FRONT FACE
	glBegin(GL_LINE_LOOP);
		glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
		glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
		glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
		glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glEnd();

	// BACK FACE
	glBegin(GL_LINE_LOOP);
		glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
		glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
		glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
		glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
	glEnd();
	
	// RIGHT FACE
	glBegin(GL_LINE_LOOP);
		glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
		glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
		glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
		glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glEnd();
	
	// LEFT FACE
	glBegin(GL_LINE_LOOP);
		glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
		glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
		glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
		glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glEnd();
}

void Renderer::DrawSquare(glm::vec3 pt1, glm::vec3 pt2, glm::vec3 pt3, glm::vec3 pt4) {
	glLineWidth(2);

	glBegin(GL_LINE_LOOP);
	glVertex3f(pt1.x, pt1.y, pt1.z);
	glVertex3f(pt2.x, pt2.y, pt2.z);
	glVertex3f(pt3.x, pt3.y, pt3.z);
	glVertex3f(pt4.x, pt4.y, pt4.z);
	glEnd();
}


void Renderer::LoadIdentityMatrix() {
	_model = glm::mat4(1.0f);
}

void Renderer::UpdateModelMatrix(glm::mat4 matrix) {
	_model = matrix;
}

void Renderer::UpdateMVP() {
	MVP = _projection * _view * _model; 
}

unsigned int Renderer::SetMatrixID(unsigned int programID) {
	return glGetUniformLocation(programID, "MVP");
}

void Renderer::SendTransformationToShader(unsigned int matrixID) {
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
}

unsigned int Renderer::SetTextureID(unsigned int programID) {
	return glGetUniformLocation(programID, "myTextureSample");
}

void Renderer::BindTexture(unsigned int texture) {
	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Renderer::SetTextureSampler(unsigned int textureID) {
	glUniform1i(textureID, 0);
}

void Renderer::DeleteBuffers(unsigned int buffer) {
	glDeleteBuffers(1, &buffer);
}

void Renderer::DeleteProgram(unsigned int programID) {
	glDeleteProgram(programID);
}

void Renderer::DeleteVrtxArray() {
	glDeleteVertexArrays(1, &_vrtxArrID);
}

void Renderer::DeleteTextures(unsigned int texture) {
	glDeleteTextures(1, &texture);
}

void Renderer::SetPerpectiveCam(float fovAngle, float aspect, float near, float far) {
	_projection = glm::perspective(glm::radians(fovAngle), aspect, near, far);
}

void Renderer::SetOrthographicCam(float left, float right, float bottom, float top, float zNear, float zFar) {
	_projection = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void Renderer::SetCamView(glm::vec3 camPos, glm::vec3 lookAt, glm::vec3 head) {
	_view = glm::lookAt(camPos, lookAt, head);
}

void Renderer::SetCamView(glm::mat4 viewMat) {
	_view = viewMat;
}



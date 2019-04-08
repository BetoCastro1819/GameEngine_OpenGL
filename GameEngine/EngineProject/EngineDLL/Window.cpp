#include "Window.h"

// GLFW
#include <GLFW\glfw3.h>

Window::Window(const int& height, const int& width, const char* name) {	

	_height = height;
	_name = name;
	_width = width;
}

Window::~Window() {
}

bool Window::Start() {	
	cout << "Window::Start()" << endl;

	// Initialize GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Fallo al inicialiar GLFW\n");
		getchar();
		return false;
	}

	// Create window
	_window = glfwCreateWindow(_width, _height, _name, NULL, NULL);
	if (!_window) {
		fprintf(stderr, "Fallo al crear Window\n");
		getchar();
		glfwTerminate();
		return false;
	}
	glfwSetWindowShouldClose((GLFWwindow*)_window, false);

	return true;
}

bool Window::Stop() {
	cout << "Window::Stop()" << endl;
	if (_window != NULL)	
		glfwDestroyWindow((GLFWwindow*)_window);

	_window = NULL;
	glfwTerminate();	
	return true;
}

bool Window::ShouldClose() {

	if (_window) {
		if (glfwGetKey((GLFWwindow*)_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose((GLFWwindow*)_window, true);
		}
		return glfwWindowShouldClose((GLFWwindow*)_window);
	}
	return true;
}

void Window::PollEvents() { 
	glfwPollEvents();
}

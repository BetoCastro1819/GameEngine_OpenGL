#include "Window.h"
#include <GLFW\glfw3.h>

Window::Window(const int& height, const int& width, const char* name) {	
	m_height = height;
	m_name = name;
	m_width = width;
	m_window = NULL;
}

Window::~Window() {
}

bool Window::Start() {	
	printf("Starting window ");

	// Initialize GLFW
	if (!glfwInit()) {
		printf("ERROR\n");
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return false;
	}

	// Create window
	m_window = glfwCreateWindow(m_width, m_height, m_name, NULL, NULL);
	if (!m_window) {
		printf("ERROR\n");
		fprintf(stderr, "Failed to initialize window\n");
		getchar();
		glfwTerminate();
		return false;
	}
	glfwSetWindowShouldClose((GLFWwindow*)m_window, false);
	printf("SUCCESS\n");
	return true;
}

bool Window::Stop() {
	cout << "Closing Window\n";
	if (m_window != NULL)	
		glfwDestroyWindow((GLFWwindow*)m_window);

	m_window = NULL;
	glfwTerminate();	
	return true;
}

bool Window::ShouldClose() {

	if (m_window) {
		if (glfwGetKey((GLFWwindow*)m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose((GLFWwindow*)m_window, true);
		}
		return glfwWindowShouldClose((GLFWwindow*)m_window);
	}
	return true;
}

void Window::PollEvents() { 
	glfwPollEvents();
}

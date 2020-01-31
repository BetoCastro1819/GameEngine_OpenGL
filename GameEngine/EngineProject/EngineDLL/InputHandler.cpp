#include <GLFW/glfw3.h>
#include "InputHandler.h"
#include "Window.h"

InputHandler* InputHandler::m_instance = NULL;

InputHandler* InputHandler::getInstance() {
	if (!m_instance)
		m_instance = new InputHandler();

	return m_instance;
}

bool InputHandler::getKeyDown(KeyCode keyCode) {
	return (glfwGetKey((GLFWwindow*)m_window->GetWindowPtr(), (int)keyCode) == GLFW_PRESS);
}
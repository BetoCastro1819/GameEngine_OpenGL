#include "Time.h"
#include <GLFW\glfw3.h>


Time::Time() {
	lastTime = glfwGetTime();
	deltaTime = 0;
}

Time::~Time() {
}

void Time::UpdateTime() {
	deltaTime = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();

	//std::cout << "Delta Time: " << deltaTime << endl;
}

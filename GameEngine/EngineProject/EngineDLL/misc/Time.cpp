#include "Time.h"
#include <GLFW\glfw3.h>


Time::Time() {
	m_lastTime = glfwGetTime();
	m_deltaTime = 0;
}

Time::~Time() { }

float Time::GetDeltaTime() { 
	return m_deltaTime; 
}

void Time::UpdateTime() {
	m_deltaTime = glfwGetTime() - m_lastTime;
	m_lastTime = glfwGetTime();

	//std::cout << "Delta Time: " << deltaTime << endl;
}

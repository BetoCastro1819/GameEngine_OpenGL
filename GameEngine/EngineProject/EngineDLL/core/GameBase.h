#pragma once
#include <iostream>
#include "../misc/Exports.h"
#include "glm/glm.hpp"

// #include <string>
//#include "../misc/Time.h"
//#include "../scene_graph/entities/Camera.h"
//#include "../physics/PhysicsManager.h"
//#include "../rendering/Renderer.h"
//#include "Window.h"
//#include "InputHandler.h"

class Window;
class Renderer;
class Camera;
class Time;
class InputHandler;
class PhysicsManager;

class ENGINEDLL_API GameBase {
protected:
	Window* m_window;
	Renderer* m_renderer;
	Camera* m_camera;
	Time* m_time;
	InputHandler* m_inputHandler;
	PhysicsManager* m_physicsManager;

	const char* _windowName;
	int _screenHeight;
	int _screenWidth;

	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate(float deltaTime) = 0;
public:
	GameBase(const int& width, const int& height, const char* name);
	virtual ~GameBase();
	bool Start();
	bool Stop();
	void Loop(); // Calcular delta time
};


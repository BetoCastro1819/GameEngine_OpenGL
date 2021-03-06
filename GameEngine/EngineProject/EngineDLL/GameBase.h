#pragma once
#include <iostream>
#include <string>
#include "Exports.h"
#include "Renderer.h"
#include "Window.h"
#include "Time.h"

class ENGINEDLL_API GameBase {
protected:
	Window* m_window;
	Renderer* m_renderer;
	Time* _time;
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


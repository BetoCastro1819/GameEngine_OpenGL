#pragma once
#include <iostream>
#include "Exports.h"

class Window;

enum KeyCode {
	SPACE = 32,
};

class ENGINEDLL_API InputHandler {
private:
	static InputHandler* m_instance;
	Window* m_window;

	InputHandler() {}

public:
	~InputHandler() {}

	static InputHandler* getInstance();

	void setWindow(Window* window) { m_window = window; }
	bool getKeyDown(KeyCode keyCode);
};


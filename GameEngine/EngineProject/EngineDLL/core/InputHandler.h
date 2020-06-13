#pragma once
#include <iostream>
#include "../misc/Exports.h"

class Window;

enum KeyCode {
	W		= 87,
	A		= 65,
	S		= 83,
	D		= 68,
	Q		= 81,
	E		= 69,
	SPACE	= 32,
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


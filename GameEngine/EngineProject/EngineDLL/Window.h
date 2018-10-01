#pragma once
#include <iostream>
#include "Exports.h"

using namespace std;

class ENGINEDLL_API Window {
private:
	void* _window;
protected:
	int _height;
	int _width;
	const char* _name;
public:
	Window(const int& height, const int& witdh, const char* name);
	~Window();
	bool Start();
	bool Stop();
	bool ShouldClose();
	void PollEvents();
	const void* GetWindowPtr() { return _window; };
};


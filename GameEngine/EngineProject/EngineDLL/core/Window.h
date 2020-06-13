#pragma once
#include <iostream>
#include "../misc/Exports.h"

using namespace std;

class ENGINEDLL_API Window {
private:
	void* m_window;
protected:
	int m_height;
	int m_width;
	const char* m_name;
public:
	Window(const int& height, const int& witdh, const char* name);
	~Window();
	bool Start();
	bool Stop();
	bool ShouldClose();
	void PollEvents();
	const void* GetWindowPtr() { return m_window; };
	int GetHeight() { return m_height; }
	int GetWidth() { return m_width; }
};


#pragma once
#include "Exports.h"
#include "Window.h"
#include "Entity.h"

class ENGINEDLL_API CharacterController {
private:
	Window* m_window;
	Entity* m_entity;

public:
	CharacterController(Window* window, Entity* entity) 
		: m_window(window), m_entity(entity) { };

	~CharacterController() { }

	void Update(float deltaTime);
};


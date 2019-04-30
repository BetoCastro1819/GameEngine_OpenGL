#include "Game.h"

Game::Game(const int& widht, const int& height, const char* name)
	: GameBase(widht, height, name) {	
}

Game::~Game() {
	if (m_material != NULL)
		delete m_material;
}

bool Game::OnStart() {

	m_material = new Material();
	
	cout << "Game has started" << endl;
	return true;
}

bool Game::OnStop() {
	cout << "Game has stopped" << endl;		
	return false;
}

bool Game::OnUpdate(float deltaTime) {
	m_Camera->Update(deltaTime);
	return true;
}
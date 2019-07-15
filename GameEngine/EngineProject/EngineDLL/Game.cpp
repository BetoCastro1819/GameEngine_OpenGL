#include "Game.h"

Game::Game(const int& widht, const int& height, const char* name)
	: GameBase(widht, height, name) {	
}

Game::~Game() {
	if (m_scene != nullptr)
		delete m_scene;
}

bool Game::OnStart() {
	m_scene = new Scene(m_renderer, m_camera);
	if (!m_scene->Start())
		return false;
	return true;
}

bool Game::OnStop() {
	cout << "\nStoping Game" << endl;		
	return false;
}

bool Game::OnUpdate(float deltaTime) {
	m_scene->Update(deltaTime);
	return true;
}
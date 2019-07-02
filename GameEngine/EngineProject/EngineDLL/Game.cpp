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
	m_camera->GetTransform()->SetPosition(0, 0, 5);
	return true;
}

bool Game::OnStop() {
	cout << "\nStoping Game" << endl;		
	return false;
}

bool Game::OnUpdate(float deltaTime) {
	m_scene->Update(deltaTime);
	m_camera->Update(deltaTime);
	return true;
}
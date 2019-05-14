#include "Game.h"

Game::Game(const int& widht, const int& height, const char* name)
	: GameBase(widht, height, name) {	
}

Game::~Game() {
	if (m_material != nullptr)
		delete m_material;

	if (m_mesh != nullptr)
		delete m_mesh;
}

bool Game::OnStart() {
	m_material = new Material();
	m_mesh = new Mesh(_renderer, m_material);
	m_mesh->SetTexture("uvtemplate.bmp");
	m_mesh->LoadOBJFromFile("suzanne.obj");
	//m_mesh->SetScale(0.01f, 0.01f, 0.01f);

	cout << "Game has started" << endl;
	return true;
}

bool Game::OnStop() {
	cout << "Game has stopped" << endl;		
	return false;
}

bool Game::OnUpdate(float deltaTime) {
	m_Camera->Update(deltaTime);
	m_mesh->Draw();

	return true;
}
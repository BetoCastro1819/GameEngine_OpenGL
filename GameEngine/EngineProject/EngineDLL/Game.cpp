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
	m_material->LoadShaders(
		"StandardVertexShader.txt",
		"StandardFragmentShader.txt"
	);
	
	m_mesh = new Mesh(m_renderer, m_material);
	m_mesh->SetShader(m_material->GetShader());
	m_mesh->SetTexture("uvtemplate.bmp");

	if (!m_mesh->LoadWithAssimp("suzanne.obj")) {
		return false;
	}
	return true;
}

bool Game::OnStop() {
	cout << "Stoping Game" << endl;		
	return false;
}

bool Game::OnUpdate(float deltaTime) {
	m_camera->Update(deltaTime);
	m_mesh->Draw();

	return true;
}
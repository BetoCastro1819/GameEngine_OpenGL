#include "Game.h"

Game::Game(const int& widht, const int& height, const char* name)
	: GameBase(widht, height, name) {	
}

Game::~Game() {
	if (m_material != nullptr)
		delete m_material;

	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (m_mesh[i] != nullptr) {
			delete m_mesh[i];
		}
	}
}

bool Game::OnStart() {
	m_material = new Material();
	m_material->LoadShaders("StandardVertexShader.txt", "StandardFragmentShader.txt");
	
	for (int i = 0; i < ARRAY_SIZE; i++) {
		m_mesh[i] = new Mesh(m_renderer, m_material);
		m_mesh[i]->SetShader(m_material->GetShader());
		m_mesh[i]->SetTexture("uvtemplate.bmp");
		if (!m_mesh[i]->LoadWithAssimp("suzanne.obj")) {
			return false;
		}
	}
	
	int meshIndex = 0;
	for (int i = 0; i < ARRAY_SIZE / 2; i++) {
		for (int j = 0; j < ARRAY_SIZE / 2; j++) {
			m_mesh[meshIndex]->SetPos((i + 1) * 2, (j + 1) * 2, 0);
			meshIndex++;
		}
	}
	return true;
}

bool Game::OnStop() {
	cout << "Stoping Game" << endl;		
	return false;
}

bool Game::OnUpdate(float deltaTime) {
	m_camera->Update(deltaTime);
	
	for (int i = 0; i < ARRAY_SIZE; i++)
		m_mesh[i]->Draw();
	
	return true;
}
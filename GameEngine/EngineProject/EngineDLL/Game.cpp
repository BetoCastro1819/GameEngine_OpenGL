#include "Game.h"

Game::Game(const int& widht, const int& height, const char* name)
	: GameBase(widht, height, name) {	
}

Game::~Game() {
	if (m_material != nullptr)
		delete m_material;

	if (m_meshParent != nullptr)
		delete m_meshParent;

	if (m_meshChild != nullptr)
		delete m_meshChild;
}

bool Game::OnStart() {
	m_material = new Material();
	m_material->LoadShaders("StandardVertexShader.txt", "StandardFragmentShader.txt");
	
	m_meshParent = new Mesh(m_renderer, m_material, "uvtemplate.bmp");
	if (!m_meshParent->LoadWithAssimp("suzanne.obj")) {
		return false;
	}
	m_meshParent->SetPos(-2, 0, 0);

	m_meshChild = new Mesh(m_renderer, m_material, "uvtemplate.bmp");
	if (!m_meshChild->LoadWithAssimp("suzanne.obj")) {
		return false;
	}
	m_meshChild->SetPos(2, 0, 0);

	m_meshParent->AddChild(m_meshChild);

	rotation = 10.0f;
	
	return true;
}

bool Game::OnStop() {
	cout << "Stoping Game" << endl;		
	return false;
}

bool Game::OnUpdate(float deltaTime) {
	m_camera->Update(deltaTime);
	
	m_meshParent->SetRotZ(rotation += deltaTime * 30);
	m_meshParent->Update();
	//m_meshChild->Draw();
	
	return true;
}
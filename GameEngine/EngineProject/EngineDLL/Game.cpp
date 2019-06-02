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

	if (m_meshChild2 != nullptr)
		delete m_meshChild2;
}

bool Game::OnStart() {
	m_material = new Material();
	m_material->LoadShaders("StandardVertexShader.txt", "StandardFragmentShader.txt");
	
	m_meshParent = new Mesh(m_renderer, m_material, "uvtemplate.bmp");
	if (!m_meshParent->LoadWithAssimp("suzanne.obj")) {
		return false;
	}
	m_meshParent->SetPos(-3, 0, 0);

	m_meshChild = new Mesh(m_renderer, m_material, "uvtemplate.bmp");
	if (!m_meshChild->LoadWithAssimp("suzanne.obj")) {
		return false;
	}

	m_meshChild2 = new Mesh(m_renderer, m_material, "uvtemplate.bmp");
	if (!m_meshChild2->LoadWithAssimp("suzanne.obj")) {
		return false;
	}


	m_meshParent->AddChild(m_meshChild);
	m_meshChild->SetPos(3, 0, 0);

	m_meshChild->AddChild(m_meshChild2);
	m_meshChild2->SetPos(3, 0, 0);

	rotation = 10.0f;
	
	return true;
}

bool Game::OnStop() {
	cout << "Stoping Game" << endl;		
	return false;
}

bool Game::OnUpdate(float deltaTime) {
	
	//m_meshParent->SetPos(
	//	(float)m_meshParent->GetPos().x,
	//	sin(rotation += deltaTime), 
	//	(float)m_meshParent->GetPos().z
	//);

	m_meshParent->SetRotZ(rotation += deltaTime * 30);
	m_meshParent->Update();

	m_camera->Update(deltaTime);

	return true;
}
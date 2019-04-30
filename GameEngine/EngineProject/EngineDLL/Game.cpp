#include "Game.h"

Game::Game(const int& widht, const int& height, const char* name)
	: GameBase(widht, height, name) {	
}

Game::~Game() {
	if (m_sprite != NULL)
		delete m_sprite;

	if (m_material != NULL)
		delete m_material;

	if (m_texture != NULL)
		delete m_texture;
}


bool Game::OnStart() {
	m_material = new Material();

	m_texture = new Texture("uvtemplate.bmp");
	m_texture->SetTextureDimensions(512, 512);
	m_texture->SetFrameDimensions(51, 51);
	m_texture->SetNumberOfFramesPerRow(10);
	m_texture->SetNumberOfFramesPerColumn(10);

	m_sprite = new Sprite(m_renderer);
	m_sprite->SetMaterial(m_material);
	m_sprite->SetTexture(m_texture);
	m_sprite->InitVertices();
	m_sprite->SetFrameID(10);

	m_sprite->SetPos(
		_window->GetWidth() / 2, 
		_window->GetHeight() / 2,
		0.0f
	);
	m_sprite->SetScale(5.0f, 5.0f, 5.0f);

	cout << "Game::OnStart()" << endl;
	return true;
}

bool Game::OnStop() {
	cout << "Game::OnStop()" << endl;		
	return false;
}

bool Game::OnUpdate(float deltaTime) {
	m_sprite->Draw();
	return true;
}
#include "Game.h"

Game::Game(const int& widht, const int& height, const char* name)
	: GameBase(widht, height, name) {	
	_fpsCount = 0;	
}

Game::~Game() {
	if (_triangle != NULL)
		delete _triangle;
	
	if (_cube != NULL)
		delete _cube;
	
	if (_circle != NULL)
		delete _circle;

	if (_tx != NULL)
		delete _tx;

	if (_player != NULL)
		delete _player;

	if (_tilemapTest != NULL)
		delete _tilemapTest;

	if (_mat != NULL)
		delete _mat;
}

bool Game::OnStart() {
	cout << "Game::OnStart()" << endl;

	_mat = new Material();

	_tilemap = new Tilemap(_renderer, 64, 64, 32, 32, 15, 20, "Tilemap2.bmp");
	if (_tilemap && _mat) {
		_tilemap->SetMaterial(_mat);
		_tilemap->SetDrawMode(3);
		_tilemap->SetPos(0, 0, 0);
	}

	// Create sprite
	_player = new Sprite(
		_renderer,				// Pointer to renderer
		10,						// Frame ID
		512,					// Texture width in pixels
		512,					// Texture height in pixels
		51,						// Width per frame in pixels
		51,						// Height per frame in pixels
		10,						// Number of horizontal frames
		10,						// Number of vertical frames
		true,					// Animated?
		"uvtemplate.bmp"
	);

	if (_player && _mat) {
		_player->InitVertices();
		_player->InitVerticesUV();
		 
		_player->SetMaterial(_mat);
		_player->SetDrawMode(1);
		_player->SetFrame(10);

		_player->SetPos(
			0,		// X
			0,		// Y
			0								// Z
		);

		_player->GetBoxCollider()->SetBoxWidth(52);
		_player->GetBoxCollider()->SetBoxHeight(52);

		std::vector<int> attackAnimation = { 40,41,42,43,44,45 };
		_player->AddAnimation("Attack", attackAnimation);
		_player->SetAnimation("Attack");
		_player->SetAnimationSpeed(10);

		CollisionManager::GetInstance()->AddToGroup(CollisionLayer::PLAYER, _player);
	}

	// Create sprite
	_collisionTest = new Sprite(
		_renderer,				// Pointer to renderer
		10,						// Frame ID
		512,					// Texture width in pixels
		512,					// Texture height in pixels
		51,						// Width per frame in pixels
		51,						// Height per frame in pixels
		10,						// Number of horizontal frames
		10,						// Number of vertical frames
		true,					// Animated?
		"uvtemplate.bmp"
	);

	if (_collisionTest && _mat) {
		_collisionTest->InitVertices();
		_collisionTest->InitVerticesUV();
		 
		_collisionTest->SetMaterial(_mat);
		_collisionTest->SetDrawMode(1);
		 
		_collisionTest->SetPos(
			_window->GetWidth() / 4,		// X
			_window->GetHeight() / 4,		// Y
			0								// Z
		);

		_collisionTest->GetBoxCollider()->SetBoxWidth(52);
		_collisionTest->GetBoxCollider()->SetBoxHeight(52);

		CollisionManager::GetInstance()->AddToGroup(CollisionLayer::DEFAULT, _collisionTest);
	}

	_player->SetScale(0.01f, 0.01f, 0.01f);

	return true;
}

bool Game::OnStop() {
	cout << "Game::OnStop()" << endl;		
	return false;
}

bool Game::OnUpdate(float deltaTime) {
	/*
	_fpsCount++;
	if (_fpsCount > 100)
		return false;
	*/
	//_cube->Draw();
	//_triangle->Draw();		
	//_circle->Draw();			
	//_tx->DrawTextureShape();
	//_tx->SetRotY(1);

	m_Camera->Update(deltaTime);

	//_player->HandleInput(_window, deltaTime);

	//CollisionManager::GetInstance()->CheckForCollisions();

	_player->DrawSprite();
	_player->PlayAnimation(deltaTime);

	//_collisionTest->DrawSprite();

	//_tilemap->DrawSprite();
	

	//_tilemapTest->PlayAnimation(deltaTime);
	//_tilemapTest->SetFrame(1);
	//_tilemapTest->DrawSprite();
	//std::cout << "Player Pos X: " << _sprite->GetPos().x << " Player Pos Y: " << _sprite->GetPos().y << std::endl;
	return true;
}
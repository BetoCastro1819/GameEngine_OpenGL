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

	_triangle = new Triangle(_renderer);
	if (_triangle && _mat) {
		_triangle->SetMaterial(_mat);
		
		// Index 0 = GL_TRIANGLES
		_triangle->SetDrawMode(0);
	}

	_cube = new ColorShape(_renderer);
	if (_cube && _mat) {
		_cube->SetMaterial(_mat);
		_cube->SetScale(.5f, .5f, .5f);

		// Index 1 = GL_TRIANGLE_STRIP
		_cube->SetDrawMode(1);
	}

	_circle = new Circle(_renderer,	0.5, 20);
	if (_circle && _mat) {
		_circle->SetMaterial(_mat);
		
		// Index 2 = GL_TRIANGLE_FAN
		_circle->SetDrawMode(2);
	}

	_tx = new TextureShape(_renderer);
	if (_tx && _mat) {
		_tx->SetMaterial(_mat);
		_tx->SetDrawMode(1);
		_tx->SetScale(0.5f, 0.5f, 0.5f);
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
		true					// Animated?
	);

	// Create sprite
	_tilemapTest = new Sprite(
		_renderer,				// Pointer to renderer
		0,						// Frame ID
		64,						// Texture width in pixels
		64,						// Texture height in pixels
		32,						// Width per frame in pixels
		32,						// Height per frame in pixels
		2,						// Number of horizontal frames
		2,						// Number of vertical frames
		true					// Animated?
	);

	if (_tilemapTest && _mat) {
		_tilemapTest->SetMaterial(_mat);
		_tilemapTest->SetDrawMode(1);
		_tilemapTest->SetScale(50.0f, 50.0f, 50.0f);

		_tilemapTest->SetPos(
			_window->GetWidth() / 4,		// X
			_window->GetHeight() / 4,		// Y
			0								// Z
		);

		_tilemapTest->GetBoxCollider()->SetBoxWidth(20);
		_tilemapTest->GetBoxCollider()->SetBoxHeight(20);

		/*
		std::vector<int> walkAnimation = { 94,95,96,97,98,99 };
		_tilemapTest->AddAnimation("Walk", walkAnimation);
		_tilemapTest->SetAnimation("Walk");
		_tilemapTest->SetAnimationSpeed(1);
		*/
		CollisionManager::GetInstance()->AddToGroup(CollisionLayer::DEFAULT, _tilemapTest);

	}

	/*
	if (_player && _mat) {
		_player->SetMaterial(_mat);
		_player->SetDrawMode(1);
		_player->SetScale(10.0f, 10.0f, 10.0f);

		_player->SetPos(
			_window->GetWidth() / 2,		// X
			_window->GetHeight() / 2,		// Y
			0								// Z
		);

		_player->GetBoxCollider()->SetBoxWidth(20);
		_player->GetBoxCollider()->SetBoxHeight(20);

		std::vector<int> attackAnimation = { 40,41,42,43,44,45 };
		_player->AddAnimation("Attack", attackAnimation);
		_player->SetAnimation("Attack");
		_player->SetAnimationSpeed(10);

		CollisionManager::GetInstance()->AddToGroup(CollisionLayer::PLAYER, _player);
	}
	*/

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

	//_player->HandleInput(_window, deltaTime);
	//
	//CollisionManager::GetInstance()->CheckForCollisions();
	//
	//_player->DrawSprite();
	//_player->PlayAnimation(deltaTime);
	//
	//_tilemapTest->PlayAnimation(deltaTime);
	
	_tilemapTest->SetFrame(1);

	_tilemapTest->DrawSprite();

	//std::cout << "Player Pos X: " << _sprite->GetPos().x << " Player Pos Y: " << _sprite->GetPos().y << std::endl;
	return true;
}
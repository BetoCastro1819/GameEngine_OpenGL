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

	return true;
}

bool Game::OnStop() {
	cout << "Game::OnStop()" << endl;		
	return false;
}

bool Game::OnUpdate() {
	/*
	_fpsCount++;
	if (_fpsCount > 100)
		return false;
	*/
	//_cube->Draw();
	//_triangle->Draw();		
	//_circle->Draw();			

	return true;
}

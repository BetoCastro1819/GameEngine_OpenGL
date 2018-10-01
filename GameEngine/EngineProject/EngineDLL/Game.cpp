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
	}

	_cube = new ColorShape(_renderer);
	if (_cube && _mat) {
		_cube->SetMaterial(_mat);
		_cube->SetScale(.5f, .5f, .5f);
	}

	_circle = new Circle(_renderer,	0.5, 20);
	if (_circle && _mat) {
		_circle->SetMaterial(_mat);
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
	//_cube->Draw();			// In Renderer DrawArrays(GL_TRIANGLE_STRIP...)
	//_triangle->Draw();		// In Renderer DrawArrays(GL_TRIANGLES...)
	_circle->Draw();			// In Renderer DrawArrays(GL_TRIANGLE_FAN...)

	return true;
}

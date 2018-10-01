#include "Game.h"

Game::Game(const int& widht, const int& height, const char* name)
	: GameBase(widht, height, name) {	
	_fpsCount = 0;	
}

Game::~Game() {
	if (_circle != NULL)
		delete _circle;
	if (_mat != NULL)
		delete _mat;
}

bool Game::OnStart() {
	cout << "Game::OnStart()" << endl;	
	_mat = new Material();
	_circle = new Circle(_renderer,	0.5 , 20);
	if (_circle && _mat) {
		_circle->SetMaterial(_mat);
		//_circle->SetScale(.5f, .5f, .5f);
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
	_circle->SetRotY(1);
	_circle->Draw();

	return true;
}

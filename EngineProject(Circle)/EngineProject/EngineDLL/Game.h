#pragma once
#include <iostream>
#include "GameBase.h"
#include "Triangle.h"
#include "Material.h"
#include "ColorShape.h"
#include "Shape.h"
#include "Circle.h"

using namespace std;

class Game : public GameBase {
protected:
	//Triangle* _triangle;
	//ColorShape* _cube;
	Circle * _circle;
	Material* _mat;
	int _fpsCount;
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
public:
	Game(const int& height, const int& widht, const char* name);
	~Game();
};


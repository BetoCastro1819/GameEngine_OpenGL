#pragma once
#include <iostream>
#include "GameBase.h"
#include "Triangle.h"
#include "Material.h"
#include "ColorShape.h"
#include "Shape.h"
#include "Circle.h"
#include "TextureShape.h"
#include "Sprite.h"

using namespace std;

class Game : public GameBase {
protected:
	TextureShape * _tx;
	Triangle* _triangle;
	ColorShape* _cube;
	Circle * _circle;
	Sprite* _sprite;
	Material* _mat;
	int _fpsCount;
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate(float deltaTime) override;
public:
	Game(const int& height, const int& widht, const char* name);
	~Game();
};


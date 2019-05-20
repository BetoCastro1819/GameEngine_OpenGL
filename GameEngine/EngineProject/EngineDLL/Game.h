#pragma once
#include <iostream>
#include "GameBase.h"
#include "Material.h"
#include "Mesh.h"

using namespace std;

const int ARRAY_SIZE = 4;
class Game : public GameBase {
protected:
	Material* m_material;
	Mesh* m_mesh[ARRAY_SIZE];

	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate(float deltaTime) override;

public:
	Game(const int& height, const int& widht, const char* name);
	~Game();
};


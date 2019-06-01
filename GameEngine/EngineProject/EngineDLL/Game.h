#pragma once
#include <iostream>
#include "GameBase.h"
#include "Material.h"
#include "Mesh.h"

using namespace std;

class Game : public GameBase {
protected:
	Material* m_material;
	Mesh* m_meshParent;
	Mesh* m_meshChild;
	
	float rotation;

	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate(float deltaTime) override;

public:
	Game(const int& height, const int& widht, const char* name);
	~Game();
};


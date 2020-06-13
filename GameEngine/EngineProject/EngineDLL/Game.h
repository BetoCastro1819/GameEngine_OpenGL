#pragma once
#include <iostream>
#include "core/GameBase.h"
#include "scene_graph/entities/Scene.h"

using namespace std;

class Game : public GameBase {
protected:
	Scene* m_scene;

	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate(float deltaTime) override;

public:
	Game(const int& height, const int& widht, const char* name);
	~Game();
};


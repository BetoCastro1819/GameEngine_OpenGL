#pragma once
#include "Exports.h"
#include "Sprite.h"
#include <map>
#include <vector>

enum CollisionLayer {
	DEFAULT,
	PLAYER,
	TILEMAP,
	NUMBER_OF_LAYERS
};

class ENGINEDLL_API CollisionManager {
private:
	static CollisionManager* instance;
	std::map<CollisionLayer, std::vector<Sprite*>> collisionGroups;

	void Collision(Sprite* obj1, Sprite* obj2);
public:
	CollisionManager();
	~CollisionManager();
	static CollisionManager* GetInstance();
	void CheckForCollisions();
	void AddToGroup(CollisionLayer layer, Sprite* sprite);
};


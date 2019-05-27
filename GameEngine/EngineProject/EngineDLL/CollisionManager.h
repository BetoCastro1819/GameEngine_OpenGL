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

	enum SeparationType {
		Vertical,
		Horizontal
	};

	void Collision(Sprite* obj1, Sprite* obj2);
	void VerticalSeparation(Sprite* obj1, Sprite* obj2, float separationValue);
	void HorizontalSeparation(Sprite* obj1, Sprite* obj2, float separationValue);

public:
	CollisionManager();
	~CollisionManager();
	static CollisionManager* GetInstance();
	void CheckForCollisions();
	void AddToGroup(CollisionLayer layer, Sprite* sprite);
};


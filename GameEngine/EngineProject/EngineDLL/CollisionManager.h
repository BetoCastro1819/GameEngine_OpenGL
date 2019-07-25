#pragma once
#include "Exports.h"
#include "Entity.h"
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
	std::map<CollisionLayer, std::vector<Entity*>> collisionGroups;

	enum SeparationType {
		Vertical,
		Horizontal
	};

	void Collision(Entity* obj1, Entity* obj2);
	void VerticalSeparation(Entity* obj1, Entity* obj2, float separationValue);
	void HorizontalSeparation(Entity* obj1, Entity* obj2, float separationValue);

public:
	CollisionManager();
	~CollisionManager();
	static CollisionManager* GetInstance();
	void CheckForCollisions();
	void AddToGroup(CollisionLayer layer, Entity* sprite);
};


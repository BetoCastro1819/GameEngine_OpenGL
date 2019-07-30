#include "CollisionManager.h"

CollisionManager* CollisionManager::instance = 0;

CollisionManager* CollisionManager::GetInstance() {
	if (instance == NULL)
		instance = new CollisionManager();
	return instance;
}

CollisionManager::CollisionManager() {
	std::vector<Entity*> emptyVector = {};

	collisionGroups.insert(
		std::pair<CollisionLayer, std::vector<Entity*>> (CollisionLayer::DEFAULT, emptyVector)
	);

	collisionGroups.insert(
		std::pair<CollisionLayer, std::vector<Entity*>> (CollisionLayer::PLAYER, emptyVector)
	);

	collisionGroups.insert(
		std::pair<CollisionLayer, std::vector<Entity*>> (CollisionLayer::TILEMAP, emptyVector)
	);
}

CollisionManager::~CollisionManager() {
}

void CollisionManager::AddToGroup(CollisionLayer layer, Entity* sprite) {
	collisionGroups.at(layer).push_back(sprite);

	std::cout << "Number of collision layers: " << sizeof(CollisionLayer) << std::endl;

	std::cout << "Number of sprites in DEFAULT layer: " << collisionGroups.at( (CollisionLayer)0 ).size() << std::endl;
	std::cout << "Number of sprites in PLAYER layer: " << collisionGroups.at(CollisionLayer::PLAYER).size() << std::endl;
	std::cout << "Number of sprites in TILEMAP layer: " << collisionGroups.at(CollisionLayer::TILEMAP).size() << std::endl;
}

void CollisionManager::CheckForCollisions() {
	int numberOfLayers = CollisionLayer::NUMBER_OF_LAYERS;

	for (int currentLayer = 0; currentLayer < numberOfLayers; currentLayer++) {

		for (int objectIndex = 0; objectIndex < collisionGroups.at((CollisionLayer)currentLayer).size(); objectIndex++) {

			for (int currentOpposingLayer = 0; currentOpposingLayer < numberOfLayers; currentOpposingLayer++) {

				if (currentLayer != currentOpposingLayer) {

					for (int currentOpposingObjIndex = 0; currentOpposingObjIndex < collisionGroups.at((CollisionLayer)currentOpposingLayer).size(); currentOpposingObjIndex++) {

						Entity* obj1 = collisionGroups.at((CollisionLayer)currentLayer)[objectIndex];
						Entity* obj2 = collisionGroups.at((CollisionLayer)currentOpposingLayer)[currentOpposingObjIndex];
						if (obj1->GetIsEnabled() && obj2->GetIsEnabled())
							Collision(obj1, obj2);
					} // Next opposing object
				}
			} // Next opposing layer
		} // Next object from current collision layer
	} // Next collision layer
}

void CollisionManager::Collision(Entity* obj1, Entity* obj2) {
	glm::vec3 diff = obj2->GetPos() - obj1->GetPos();
	
	float modX = glm::abs(diff.x);
	float modY = glm::abs(diff.y);

	float collisionDistance_X = obj1->GetBoxCollider()->GetBoxWidth() / 2 + obj2->GetBoxCollider()->GetBoxWidth() / 2;
	float collisionDistance_Y = obj1->GetBoxCollider()->GetBoxHeight() / 2 + obj2->GetBoxCollider()->GetBoxHeight() / 2;

	if (modX < collisionDistance_X && modY < collisionDistance_Y) {

		float overlapAreaWidth = collisionDistance_X - modX;
		float overlapAreaHeight = collisionDistance_Y - modY;

		if (overlapAreaWidth > overlapAreaHeight)
			VerticalSeparation(obj1, obj2, overlapAreaHeight);
		else
			HorizontalSeparation(obj1, obj2, overlapAreaWidth);
	}
}

void CollisionManager::VerticalSeparation(Entity* obj1, Entity* obj2, float separationValue) {
	if (obj1->GetPos().y < obj2->GetPos().y) {
		obj1->Translate(0, -(separationValue / 2), 0);
		obj2->Translate(0, (separationValue / 2), 0);

		obj1->GetBoxCollider()->SetCollisionFlag_top(true);
		obj2->GetBoxCollider()->SetCollisionFlag_bottom(true);

		obj1->GetBoxCollider()->SetCollidingEntity(obj2);
		obj2->GetBoxCollider()->SetCollidingEntity(obj1);
	}
	else {
		obj1->Translate(0, (separationValue / 2), 0);
		obj2->Translate(0, -(separationValue / 2), 0);

		obj1->GetBoxCollider()->SetCollisionFlag_bottom(true);
		obj2->GetBoxCollider()->SetCollisionFlag_top(true);

		obj1->GetBoxCollider()->SetCollidingEntity(obj2);
		obj2->GetBoxCollider()->SetCollidingEntity(obj1);
	}
}

void CollisionManager::HorizontalSeparation(Entity* obj1, Entity* obj2, float separationValue) {
	if (obj1->GetPos().x < obj2->GetPos().x) {
		obj1->Translate(-(separationValue / 2), 0, 0);
		obj2->Translate((separationValue / 2), 0, 0);

		obj1->GetBoxCollider()->SetCollisionFlag_right(true);
		obj2->GetBoxCollider()->SetCollisionFlag_left(true);

		obj1->GetBoxCollider()->SetCollidingEntity(obj2);
		obj2->GetBoxCollider()->SetCollidingEntity(obj1);
	}
	else {
		obj1->Translate((separationValue / 2), 0, 0);
		obj2->Translate(-(separationValue / 2), 0, 0);

		obj1->GetBoxCollider()->SetCollisionFlag_left(true);
		obj2->GetBoxCollider()->SetCollisionFlag_right(true);

		obj1->GetBoxCollider()->SetCollidingEntity(obj2);
		obj2->GetBoxCollider()->SetCollidingEntity(obj1);
	}
}
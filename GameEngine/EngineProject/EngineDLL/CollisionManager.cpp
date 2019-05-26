#include "CollisionManager.h"

CollisionManager* CollisionManager::instance = 0;
CollisionManager* CollisionManager::GetInstance() {
	if (instance == NULL) {
		instance = new CollisionManager();
	}
	return instance;
}

CollisionManager::CollisionManager() {
	std::vector<Sprite*> emptyVector = {};

	collisionGroups.insert(
		std::pair<CollisionLayer, std::vector<Sprite*>> (CollisionLayer::DEFAULT, emptyVector)
	);

	collisionGroups.insert(
		std::pair<CollisionLayer, std::vector<Sprite*>> (CollisionLayer::PLAYER, emptyVector)
	);

	collisionGroups.insert(
		std::pair<CollisionLayer, std::vector<Sprite*>> (CollisionLayer::TILEMAP, emptyVector)
	);
}

CollisionManager::~CollisionManager() {
}

void CollisionManager::AddToGroup(CollisionLayer layer, Sprite* sprite) {
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
			
			// Check for collision between select object and obejcts from the other layers

			for (int currentOpposingLayer = 0; currentOpposingLayer < numberOfLayers; currentOpposingLayer++) {
				
				// If it's not the same layer
				// Check for collision
				if (currentLayer != currentOpposingLayer) {
				
					// Loop between current object and the object from the other layers
					for (int currentOpposingObjIndex = 0; currentOpposingObjIndex < collisionGroups.at((CollisionLayer)currentOpposingLayer).size(); currentOpposingObjIndex++) {

						Sprite* obj1 = collisionGroups.at((CollisionLayer)currentLayer)[objectIndex];
						Sprite* obj2 = collisionGroups.at((CollisionLayer)currentOpposingLayer)[currentOpposingObjIndex];
						Collision(obj1, obj2);
					} // Next opposing object
				}

			} // Next opposing layer

		} // Next object from current collision layer

	} // Next collision layer
}

void CollisionManager::Collision(Sprite* obj1, Sprite* obj2) {
	
	glm::vec3 diff;

	diff = obj2->GetPos() - obj1->GetPos();
	
	float modX = glm::abs(diff.x);
	//std::cout << "diff.x: " << diff.x << std::endl;

	float modY = glm::abs(diff.y);
	//std::cout << "diff.y: " << diff.y << std::endl;

	// If there is a collision
	if (modX < obj1->GetBoxCollider()->GetBoxWidth() / 2 + obj2->GetBoxCollider()->GetBoxWidth() / 2 &&
		modY < obj1->GetBoxCollider()->GetBoxHeight() / 2 + obj2->GetBoxCollider()->GetBoxHeight() / 2) {

		std::cout << "Collision detected" << std::endl;
		
		//std::cout << "modX: " << modX << std::endl;
		//std::cout << "modY: " << modY << std::endl;

		// Penetration distance on X and Y axis
		float penX = obj1->GetBoxCollider()->GetBoxWidth() / 2 + obj2->GetBoxCollider()->GetBoxWidth() / 2 - modX;
		float penY = obj1->GetBoxCollider()->GetBoxHeight() / 2 + obj2->GetBoxCollider()->GetBoxHeight() / 2 - modY;

		if (penX > penY) {

			std::cout << "Vertical Penetration" << std::endl;

			// Vertical penetration
			if (obj1->GetPos().y < obj2->GetPos().y) {
				

				// obj1 is BELOW obj2
				// Reposition objs accordingly
				obj1->SetPos(obj1->GetPos().x, 
							 obj1->GetPos().y - penY / 2, 
							 obj1->GetPos().z);

				obj2->SetPos(obj2->GetPos().x,
							 obj2->GetPos().y + penY / 2,
							 obj2->GetPos().z);
			}
			else {

				// obj1 is ABOVE obj2
				// Reposition objs accordingly
				obj1->SetPos(obj1->GetPos().x,
							 obj1->GetPos().y + penY / 2,
							 obj1->GetPos().z);

				obj2->SetPos(obj2->GetPos().x,
							 obj2->GetPos().y - penY / 2,
							 obj2->GetPos().z);
			}
		}
		else {
		
			std::cout << "Horizontal Penetration" << std::endl;

			// Horizontal penetration
			if (obj1->GetPos().x < obj2->GetPos().x) {

				// obj1 is on the LEFT SIDE of obj2
				// Reposition accordingly
				obj1->SetPos(obj1->GetPos().x - penX / 2,
							 obj1->GetPos().y,
							 obj1->GetPos().z);

				obj2->SetPos(obj2->GetPos().x + penX / 2,
							 obj2->GetPos().y,
							 obj2->GetPos().z);
			}
			else {

				// obj1 is on the RIGHT SIDE of obj2
				// Reposition accordingly
				obj1->SetPos(obj1->GetPos().x + penX / 2,
							 obj1->GetPos().y,
							 obj1->GetPos().z);

				obj2->SetPos(obj2->GetPos().x - penX / 2,
							 obj2->GetPos().y,
							 obj2->GetPos().z);
			}
		}
	}
}
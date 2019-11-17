#include "Scene.h"
#include "Transform.h"

Scene::Scene(Renderer* renderer, Camera* camera) : Entity(renderer) {
	m_camera = camera;
	SetName("Scene");

	AddNode(m_camera);
	m_camera->GetTransform()->SetPosition(0.0f, 0.0f, 20.0f);
}

bool Scene::Start() {

	m_suzanne = new Suzzane(m_renderer);
	m_suzanne->SetName("Suzanne");
	m_suzanne->GetTransform()->SetPosition(0.0f, 0.0f, 0.0f);
	AddNode(m_suzanne);

	//m_suzanne->GetChildrenByIndex(2)->GetTransform()->SetPosition(6.0f, 0.0f, 0.0f);

	m_suzanne_1 = nullptr;
	//m_suzanne_1 = new Suzzane(m_renderer);
	//m_suzanne_1->SetName("Suzanne right");
	//m_suzanne->AddNode(m_suzanne_1);
	//m_suzanne_1->GetTransform()->SetPosition(6.0f, 0.0f, 0.0f);

	m_rotationSpeed = 50.0f;

	FillVectorWithEntitiesInScene();

	return true;
}

void Scene::Update(float deltaTime) {
	Entity::Update(deltaTime);

	//m_camera->TestForVisibility(m_suzanne);

	//m_suzanne->GetTransform()->Yaw(m_rotationSpeed * deltaTime);
}

void Scene::FillVectorWithEntitiesInScene() {
	m_suzanne->GetAllChildren(m_entities);
	printf("\nNumber of entities in scene %d\n", m_entities.size());

	for (int i = 0; i < m_entities.size(); i++) {
		if (is_bsp_plane((Entity*)m_entities[i])) {
			Plane bsp_plane;

			const char* entityName = ((Entity*)m_entities[i])->GetName();
			if (entityName[4] == 'r') {
				m_camera->AddPlane(bsp_plane.CreatePlaneFromPointAndNormal(
					((Entity*)m_entities[i])->GetTransform()->GetBoundingBox().minVertex,
					World::right
				));
			}
			else if (entityName[4] == 'f') {
				m_camera->AddPlane(bsp_plane.CreatePlaneFromPointAndNormal(
					((Entity*)m_entities[i])->GetTransform()->GetBoundingBox().minVertex,
					World::foward
				));
			}
		}
		else {
			m_camera->AddEntity((Entity*)m_entities[i]);
		}
	}
}

bool Scene::is_bsp_plane(Entity* entity) const {
	bool isBspPlane = 
		entity->GetName()[0] == 'b' &&
		entity->GetName()[1] == 's' &&
		entity->GetName()[2] == 'p';

	return isBspPlane;
}

Scene::~Scene() {
	if (m_suzanne != nullptr) delete m_suzanne;
	if (m_suzanne_1 != nullptr) delete m_suzanne_1;
}

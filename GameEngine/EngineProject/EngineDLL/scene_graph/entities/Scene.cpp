#include "Scene.h"
#include "Transform.h"

Scene::Scene(Renderer* renderer, Camera* camera) : Entity(renderer) {
	m_camera = camera;
	SetName("Scene");

	AddNode(m_camera);
	Transform* cameraTransform = m_camera->GetTransform();
	cameraTransform->SetPosition(-10.0f, 10.0f, -15.0f);
	cameraTransform->Yaw(20);
	cameraTransform->Pitch(30);
}

bool Scene::Start() {
	m_suzanne = new Suzzane(m_renderer, false, glm::vec3(0, 8, 0));
	m_suzanne->SetName("Suzanne");
	AddNode(m_suzanne);

	m_terrain = new Terrain(m_renderer, glm::vec3(0, -5, 0));
	m_terrain->SetName("Terrain");
	AddNode(m_terrain);

	m_landingPad = new LandingPad(m_renderer, glm::vec3(0, 0, 0));
	m_landingPad->SetName("LandingPad");
	AddNode(m_landingPad);

	return true;
}

void Scene::Update(float deltaTime) {
	Entity::Update(deltaTime);
}

void Scene::FillVectorWithEntitiesInScene() {
	m_suzanne->FillArrayWithChildren(m_entities);
	printf("\nNumber of entities in scene %d\n", m_entities.size());

	for (int i = 0; i < m_entities.size(); i++) {
		if (is_bsp_plane((Entity*)m_entities[i])) {
			Plane bsp_plane;

			const char* entityName = ((Entity*)m_entities[i])->GetName();
			if (entityName[4] == 'r') {
				m_camera->AddPlane(bsp_plane.CreatePlaneFromPointAndNormal(
					((Entity*)m_entities[i])->GetTransform()->GetBoundingBox()->minVertex,
					World::right
				));
			}
			else if (entityName[4] == 'f') {
				m_camera->AddPlane(bsp_plane.CreatePlaneFromPointAndNormal(
					((Entity*)m_entities[i])->GetTransform()->GetBoundingBox()->minVertex,
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
	if (m_terrain != nullptr) delete m_terrain;
	if (m_landingPad != nullptr) delete m_landingPad;
}

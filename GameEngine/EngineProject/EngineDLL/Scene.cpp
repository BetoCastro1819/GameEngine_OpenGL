#include "Scene.h"
#include "Transform.h"

Scene::Scene(Renderer* renderer, Camera* camera) : Entity(renderer) {
	m_camera = camera;
	SetName("Scene");

	AddNode(m_camera);
	m_camera->GetTransform()->SetPosition(0.0f, 0.0f, 10.0f);
}

bool Scene::Start() {

	m_suzanne = new Suzzane(m_renderer);
	m_suzanne->SetName("Suzanne left");
	m_suzanne->GetTransform()->SetPosition(0.0f, 0.0f, 0.0f);
	AddNode(m_suzanne);

	m_suzanne_1 = new Suzzane(m_renderer);
	m_suzanne_1->SetName("Suzanne right");
	m_suzanne->AddNode(m_suzanne_1);
	m_suzanne_1->GetTransform()->SetPosition(3.0f, 0.0f, 0.0f);


	m_rotationSpeed = 50.0f;

	return true;
}

void Scene::Update(float deltaTime) {
	Entity::Update(deltaTime);


	m_camera->TestForFrustrumCulling(m_suzanne);
	m_camera->TestForFrustrumCulling(m_suzanne_1);

	//m_suzanne_1->GetTransform()->SetPosition(3.0f, 0.0f, 0.0f);
	//m_suzanne->GetTransform()->Yaw(m_rotationSpeed * deltaTime);
}

Scene::~Scene() {
	if (m_suzanne != nullptr) delete m_suzanne;
	if (m_suzanne_1 != nullptr) delete m_suzanne_1;
}

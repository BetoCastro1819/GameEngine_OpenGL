#include "Scene.h"
#include "Transform.h"

Scene::Scene(Renderer* renderer, Camera* camera) : Entity(renderer) {
	m_camera = camera;
}

bool Scene::Start() {
	m_suzzane1 = new Suzzane(m_renderer);
	m_suzzane1->GetTransform()->SetScale(0.5f, 0.5f, 0.5f);
	m_suzzane1->GetTransform()->SetPosition(-3, 0, 0);
	AddNode(m_suzzane1);

	m_suzzane2 = new Suzzane(m_renderer);
	m_suzzane2->GetTransform()->SetPosition(6, 0, 0);
	m_suzzane1->AddNode(m_suzzane2);

	m_suzzane3 = new Suzzane(m_renderer);
	m_suzzane3->GetTransform()->SetPosition(3, 0, 0);
	m_suzzane2->AddNode(m_suzzane3);

	m_rotationSpeed = 1;

	return true;
}

void Scene::Update(float deltaTime) {
	float speed = m_rotationSpeed * deltaTime;

	m_suzzane1->GetTransform()->Roll(m_rotationSpeed);
	m_suzzane2->GetTransform()->Roll(m_rotationSpeed);
	m_suzzane3->GetTransform()->Roll(m_rotationSpeed);

	SceneNode::Update(deltaTime);
}

Scene::~Scene() {
	if (m_suzzane1 != nullptr) delete m_suzzane1;
}

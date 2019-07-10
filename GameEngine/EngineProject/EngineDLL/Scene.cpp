#include "Scene.h"
#include "Transform.h"

Scene::Scene(Renderer* renderer, Camera* camera) : Entity(renderer) {
	m_camera = camera;
}

bool Scene::Start() {
	m_cubeTest = new Suzzane(m_renderer);
	m_cubeTest->GetTransform()->SetScale(0.5f, 0.5f, 0.5f);
	AddNode(m_cubeTest);

	m_cubeTest->GetChildrenByIndex(2)->GetTransform()->SetPosition(5, 0, 0);
	m_cubeTest->GetChildrenByIndex(3)->GetTransform()->SetPosition(-5, 0, 0);

	m_rotationSpeed = 10;

	return true;
}

void Scene::Update(float deltaTime) {
	float speed = m_rotationSpeed * deltaTime;
	m_cubeTest->GetTransform()->Yaw(speed);

	SceneNode::Update(deltaTime);
}

Scene::~Scene() {
	if (m_cubeTest != nullptr) delete m_cubeTest;
}

#include "Scene.h"
#include "Transform.h"

Scene::Scene(Renderer* renderer, Camera* camera) : Entity(renderer) {
	m_camera = camera;
}

bool Scene::Start() {
	m_cubeTest = new Suzzane(m_renderer);
	m_cubeTest->GetTransform()->SetScale(0.5f, 0.5f, 0.5f);
	AddNode(m_cubeTest);

	m_rotationSpeed = 10;

	return true;
}

void Scene::Update(float deltaTime) {
	//float speed = m_rotationSpeed * deltaTime;
	
	SceneNode::Update(deltaTime);
}

Scene::~Scene() {
	if (m_cubeTest != nullptr) delete m_cubeTest;
}

#include "Scene.h"
#include "Transform.h"

Scene::Scene(Renderer* renderer, Camera* camera) : Entity(renderer) {
	m_camera = camera;
}

bool Scene::Start() {
	m_suzzane = new Suzzane(m_renderer);
	m_suzzane->GetTransform()->SetScale(0.5f, 0.5f, 0.5f);
	m_suzzane->GetTransform()->SetPosition(0, 0, 0);
	AddNode(m_suzzane);

	return true;
}

void Scene::Update(float deltaTime) {
	SceneNode::Update(deltaTime);
}

Scene::~Scene() {
	if (m_suzzane != nullptr) delete m_suzzane;
}

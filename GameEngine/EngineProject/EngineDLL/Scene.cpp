#include "Scene.h"
#include "Transform.h"

Scene::Scene(Renderer* renderer, Camera* camera) : Entity(renderer) {
	m_camera = camera;
}

bool Scene::Start() {
	m_suzzanne = new Suzzane(m_renderer);
	m_suzzanne->GetTransform()->SetScale(0.5f, 0.5f, 0.5f);
	m_suzzanne->GetTransform()->SetPosition(0, 0, 0);
	AddNode(m_suzzanne);

	//mesh = new Suzzane(m_renderer);
	//mesh->GetTransform()->SetPosition(4, 0, 0);
	//AddNode(mesh);
	//m_suzzanne->AddNode(mesh);

	AddNode(m_camera);
	m_camera->GetTransform()->SetPosition(0, 0, 5);

	//SceneNode* rootNode = m_cubeTest->GetChildrenByIndex(0);
	//SceneNode* arms = rootNode->GetChildrenByIndex(3);
	//
	//arms->GetTransform()->SetPosition(-5, 0, 0);

	m_rotationSpeed = 10;

	return true;
}

void Scene::Update(float deltaTime) {
	float speed = m_rotationSpeed * deltaTime;
	//m_suzzanne->GetTransform()->Yaw(speed);

	m_camera->TestForFrustrumCulling(m_suzzanne);
	SceneNode::Update(deltaTime);
}

Scene::~Scene() {
	if (m_suzzanne != nullptr) delete m_suzzanne;
	//if (mesh != nullptr) delete mesh;
}

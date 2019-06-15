#include "Scene.h"

Scene::Scene(Renderer* renderer, Camera* camera) : Entity(renderer) {
	m_camera = camera;
}

bool Scene::Start() {
	m_suzzane = new Suzzane(m_renderer);
	AddNode(m_suzzane);
	return true;

	//m_material = new Material();
	//m_material->LoadShaders("StandardVertexShader.txt", "StandardFragmentShader.txt");

	//m_meshParent = new Mesh(m_renderer, m_material, "uvtemplate.bmp");
	//if (!m_meshParent->LoadWithAssimp("suzanne.obj")) {
	//	return false;
	//}
	//AddChild(m_meshParent);
	//m_meshParent->SetPos(0, 0, 0);
	//
	//m_meshChild = new Mesh(m_renderer, m_material, "uvtemplate.bmp");
	//if (!m_meshChild->LoadWithAssimp("suzanne.obj")) {
	//	return false;
	//}
	//AddChild(m_meshChild);
	//
	//m_meshChild2 = new Mesh(m_renderer, m_material, "uvtemplate.bmp");
	//if (!m_meshChild2->LoadWithAssimp("suzanne.obj")) {
	//	return false;
	//}
	//AddChild(m_meshChild2);
	//
	//m_meshParent->AddChild(m_meshChild);
	//m_meshChild->SetPos(6, 0, 0);
	//
	//m_meshChild->AddChild(m_meshChild2);
	//m_meshChild2->SetPos(3, 0, 0);
	//
	//m_camera->SetPosition(0, 0, 20);
	//
	//m_rotationSpeed = 10.0f;
}

void Scene::Update(float deltaTime) {
	//m_meshParent->SetRotZ(m_rotationSpeed += deltaTime * 30);
	//m_meshChild->SetRotZ(m_rotationSpeed);
	//m_meshChild2->SetRotZ(m_rotationSpeed);
	
	SceneNode::Update(deltaTime);
}

Scene::~Scene() {
	if (m_suzzane != nullptr) delete m_suzzane;
}

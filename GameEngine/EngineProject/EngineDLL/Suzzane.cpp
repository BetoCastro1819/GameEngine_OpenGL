#include "Suzzane.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"
#include "PhysicsComponent.h"


Suzzane::Suzzane(Renderer* renderer) : Entity(renderer) {
	SetName("suzanne");

	m_material = new Material(this);
	m_material->LoadShaders("StandardVertexShader.txt", "StandardFragmentShader.txt");
	AddComponent(m_material);

	m_mesh = new Mesh(this, renderer, m_material, "uvtemplate.bmp");
	m_mesh->LoadModel("suzanne.obj");
	AddComponent(m_mesh);

	m_physicsComponent = new PhysicsComponent(this);

	printf("\nNode hierarchy from %s:\n", GetName());
	PrintNodeHierarchy();

	//GetTransform()->SetBoundingBoxDimensions(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1));
}

Suzzane::~Suzzane() {
	if (m_material != nullptr) delete m_material;
	if (m_mesh != nullptr) delete m_mesh;
}

void Suzzane::Update(float deltaTime) {
	Entity::Update(deltaTime);
}

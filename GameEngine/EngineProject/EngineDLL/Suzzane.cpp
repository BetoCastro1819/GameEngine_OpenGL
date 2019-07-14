#include "Suzzane.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"
#include "PhysicsComponent.h"


Suzzane::Suzzane(Renderer* renderer) : Entity(renderer) {
	m_material = new Material(this);
	m_material->LoadShaders("StandardVertexShader.txt", "StandardFragmentShader.txt");
	AddComponent(m_material);

	m_mesh = new Mesh(this, renderer, m_material, "uvtemplate.bmp");
	m_mesh->LoadModel("crysis.obj");
	AddComponent(m_mesh);

	m_physicsComponent = new PhysicsComponent(this);

	SetName("Crysis");

	printf("\nNumber of children: %d", m_children.size());
}

Suzzane::~Suzzane() {
	if (m_material != nullptr) delete m_material;
	if (m_mesh != nullptr) delete m_mesh;
}

void Suzzane::Update(float deltaTime) {
	Entity::Update(deltaTime);
}

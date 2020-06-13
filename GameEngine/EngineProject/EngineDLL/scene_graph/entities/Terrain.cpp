#include "Terrain.h"
#include "../../components/Material.h"
#include "../../components/Mesh.h"
#include "../../components/Transform.h"
#include "../../components/RigidBody.h"
#include "../../physics/PhysicsManager.h"

Terrain::Terrain(Renderer* renderer, glm::vec3 startPosition) : Entity(renderer) {
	SetName("Terrain root");

	m_material = new Material(this);
	m_material->LoadShaders("StandardVertexShader.txt", "StandardFragmentShader.txt");
	AddComponent(m_material);

	m_mesh = new Mesh(this, renderer, m_material, "terrain_texture.bmp");
	m_mesh->LoadModel("terrain.obj");
	AddComponent(m_mesh);

	// TODO: make this entity have childs bounding box dimension (this entity is root, not actuak mesh)

	m_transform->SetBoundingBoxDimensions(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	m_transform->SetPosition(startPosition);

	m_rigidBody = new RigidBody(this);
	m_rigidBody->CreateRigidBody(
		true,	// is static?
		1.0f,	// mass
		3.0f,	// angular damping
		0.25f,	// static friction
		0.25f,	// dynamic friction
		0.25f	// restitution
	);
	AddComponent(m_rigidBody);

	printf("\nNode hierarchy from %s:\n", GetName());
	PrintNodeHierarchy();
}


Terrain::~Terrain() {
	if (m_material != nullptr) delete m_material;
	if (m_mesh != nullptr) delete m_mesh;
	if (m_rigidBody != nullptr) delete m_rigidBody;
}

void Terrain::Update(float deltaTime) {
	Entity::Update(deltaTime);
}
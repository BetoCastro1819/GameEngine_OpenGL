#include "Suzzane.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"
#include "RigidBody.h"
#include "InputHandler.h"

Suzzane::Suzzane(Renderer* renderer) : Entity(renderer) {
	SetName("suzanne root");

	m_material = new Material(this);
	m_material->LoadShaders("StandardVertexShader.txt", "StandardFragmentShader.txt");
	AddComponent(m_material);

	m_mesh = new Mesh(this, renderer, m_material, "uvtemplate.bmp");
	m_mesh->LoadModel("suzanne.obj");
	AddComponent(m_mesh);

	// TODO: make this entity have childs bounding box dimension (this entity is root, not actuak mesh)

	m_transform->SetBoundingBoxDimensions(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	m_transform->GetBoundingBox()->maxVertex;
	m_transform->GetBoundingBox()->minVertex;

	m_rigidBody = new RigidBody(this);
	m_rigidBody->CreateRigidBody(
		false,	// is static?
		1.0f,	// mass
		0.25f,	// static friction
		0.25f,	// dynamic friction
		0.25f	// restitution
	);
	AddComponent(m_rigidBody);


	printf("\nNode hierarchy from %s:\n", GetName());
	PrintNodeHierarchy();

}

Suzzane::~Suzzane() {
	if (m_material != nullptr) delete m_material;
	if (m_mesh != nullptr) delete m_mesh;
	if (m_rigidBody != nullptr) delete m_rigidBody;
}

void Suzzane::Update(float deltaTime) {
	Entity::Update(deltaTime);

	HandleInput(deltaTime);
}

void Suzzane::HandleInput(float deltaTime) {
	InputHandler* inputHandler = InputHandler::getInstance();

	if (inputHandler->getKeyDown(KeyCode::SPACE)) {
		ActivateThrust(deltaTime);
	}
}

void Suzzane::ActivateThrust(float deltaTime) {
	glm::vec3 thrustersForce = m_transform->up * 20.0f;
	m_rigidBody->AddForce(thrustersForce, ForceType::FORCE);

	// TODO: fuel need to be consumed
}

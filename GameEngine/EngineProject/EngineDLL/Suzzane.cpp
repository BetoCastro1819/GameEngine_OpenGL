#include "Suzzane.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"
#include "RigidBody.h"
#include "InputHandler.h"
#include "SimulationEventCallback.h"
#include "PhysicsManager.h"

Suzzane::Suzzane(Renderer* renderer, bool isStatic, glm::vec3 startPosition) : Entity(renderer) {
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

	m_transform->SetPosition(startPosition);

	m_rigidBody = new RigidBody(this);
	m_rigidBody->CreateRigidBody(
		isStatic,	// is static?
		1.0f,	// mass
		3.0f,	// angular damping
		0.25f,	// static friction
		0.25f,	// dynamic friction
		0.25f	// restitution
	);
	AddComponent(m_rigidBody);

	m_simulationCallback = new SimulationEventCallback(m_rigidBody->GetRigidActor());
	PhysicsManager::getInstance()->setSimulationEventCallback(m_simulationCallback);

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
	float torqueForce = 2.0f;

	if (inputHandler->getKeyDown(KeyCode::SPACE)) {
		ActivateThrust(deltaTime);
	}

	
	// PITCH
	if (inputHandler->getKeyDown(KeyCode::W)) {
		Rotate(m_transform->right * -torqueForce);
	}
	if (inputHandler->getKeyDown(KeyCode::S)) {
		Rotate(m_transform->right * torqueForce);
	}

	// YAW
	if (inputHandler->getKeyDown(KeyCode::Q)) {
		Rotate(m_transform->up * torqueForce);
	}
	if (inputHandler->getKeyDown(KeyCode::E)) {
		Rotate(m_transform->up * -torqueForce);
	}

	// ROLL
	if (inputHandler->getKeyDown(KeyCode::D)) {
		Rotate(m_transform->foward * torqueForce);
	}
	if (inputHandler->getKeyDown(KeyCode::A)) {
		Rotate(m_transform->foward * -torqueForce);
	}
}

void Suzzane::ActivateThrust(float deltaTime) {
	glm::vec3 thrustersForce = m_transform->up * 2.0f;
	m_rigidBody->AddForce(thrustersForce, ForceType::FORCE);

	// TODO: fuel need to be consumed
}

void Suzzane::Rotate(const glm::vec3& torque) {
	m_rigidBody->AddTorque(torque, ForceType::FORCE);
}

void Suzzane::SetRigidBodyPosition(float x, float y, float z) {
	m_rigidBody->SetActorPosition(glm::vec3(x, y, z));
}


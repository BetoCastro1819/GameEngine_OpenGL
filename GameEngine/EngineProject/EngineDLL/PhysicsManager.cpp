#include <PxPhysicsAPI.h>
#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::m_instance = NULL;

PhysicsManager* PhysicsManager::getInstance() {
	if (!m_instance)
		m_instance = new PhysicsManager();

	return m_instance;
}

void PhysicsManager::deleteInstance() {
	if (m_instance)
		delete m_instance;
}

PhysicsManager::PhysicsManager() : m_pxFoundation(NULL), m_pxPhysics(NULL), m_pxScene(NULL), m_pxCooking(NULL) {
}

PhysicsManager::~PhysicsManager() {
}

physx::PxFilterFlags createFilterShader(
	physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0,
	physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1,
	physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize) 
{
	// let triggers through
	if (physx::PxFilterObjectIsTrigger(attributes0) || physx::PxFilterObjectIsTrigger(attributes1)) {
		pairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
		return physx::PxFilterFlag::eDEFAULT;
	}
	// generate contacts for all the were not filtered above
	pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;

	// trigger the contact callback for pairs (A, B) where
	// the filtermask of A containsthe ID of B and vice-versa
	pairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;

	return physx::PxFilterFlag::eDEFAULT;
}

bool PhysicsManager::start(glm::vec3 gravity, unsigned int numberOfThreads) {
	static physx::PxDefaultAllocator defaultAllocator;
	static physx::PxDefaultErrorCallback defaultErrorCallback;

	m_pxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocator, defaultErrorCallback);
	if (!m_pxFoundation) {
		printf("Failed to initialize PxFoundation\n");
		return false;
	}

	m_pxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_pxFoundation, physx::PxTolerancesScale());
	if (!m_pxPhysics) {
		printf("Failed to initialize PxPhysics\n");
		return false;
	}

	m_pxCooking = PxCreateCooking(PX_PHYSICS_VERSION, *m_pxFoundation, physx::PxCookingParams(m_pxPhysics->getTolerancesScale()));
	if (!m_pxCooking) {
		printf("Failed to initialize PxCooking\n");
		return false;
	}

	physx::PxSceneDesc sceneDesc(m_pxPhysics->getTolerancesScale());

	physx::PxVec3 physxGravity(gravity.x, gravity.y, gravity.z);
	sceneDesc.gravity = physxGravity;
	sceneDesc.kineKineFilteringMode = physx::PxPairFilteringMode::eKEEP;
	sceneDesc.staticKineFilteringMode = physx::PxPairFilteringMode::eKEEP;

	sceneDesc.filterShader = createFilterShader;

	if (!sceneDesc.cpuDispatcher) {
		physx::PxDefaultCpuDispatcher* cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(numberOfThreads);
		sceneDesc.cpuDispatcher = cpuDispatcher;
	}

	if (!sceneDesc.filterShader)
		sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;

	if (!sceneDesc.isValid()) {
		printf("The scene descriptor is not valid\n");
		return false;
	}
		 
	m_pxScene = m_pxPhysics->createScene(sceneDesc);
	if (!m_pxScene) {
		printf("Failed to create PxScene\n");
		return false;
	}

	m_pxScene->setVisualizationParameter(physx::PxVisualizationParameter::eSCALE, 1.0f);
	m_pxScene->setVisualizationParameter(physx::PxVisualizationParameter::eWORLD_AXES, 10.0f);
	m_pxScene->setVisualizationParameter(physx::PxVisualizationParameter::eACTOR_AXES, 5.0f);
	m_pxScene->setVisualizationParameter(physx::PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);

	return false;
}
void PhysicsManager::stop() {

}

void PhysicsManager::simulate(float deltaTime) {

}

void PhysicsManager::fetchSimulationResults() {

}

void PhysicsManager::addActor(physx::PxActor* actor) {

}

void PhysicsManager::removeActor(physx::PxActor* actor) {

}

void PhysicsManager::setCurrentSceneGravity(glm::vec3 gravity) {

}

void PhysicsManager::setSimulationEventCallback(physx::PxSimulationEventCallback* simulationCallback) {

}

physx::PxMaterial* PhysicsManager::createPhysicsMaterial(float staticFriction, float dynamicFriction, float restitution) {
	return NULL;
}

physx::PxActor* PhysicsManager::createRigidActor(physx::PxTransform pxTransform, bool isStatic) {
	return NULL;
}

physx::PxHeightField* PhysicsManager::createHeighField(physx::PxHeightFieldDesc hfDesc) {
	return NULL;
}
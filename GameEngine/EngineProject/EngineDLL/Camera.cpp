#include "Camera.h"
#include "Transform.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

Camera::Camera(Renderer* renderer, Window* window) : Entity(renderer) {
	SetName("Camera");

	m_Window = window;

	m_CameraTarget = glm::vec3(0, 0, 0);
	m_strafeSpeed = 10.0f;
	m_RotationSpeed = 100.0f;
	//m_transform->Yaw(180);

	zNear = 0.1f;
	zFar = 100.0f;
	fov = 45;
	aspectRatio = (float)m_Window->GetWidth() / (float)m_Window->GetHeight();

	m_renderer->SetPerpectiveCam(fov, aspectRatio, zNear, zFar);

	UpdateViewMatrix();

	m_previouslyVisibleEntities = m_currentlyVisibleEntities;
}

void Camera::Update(float deltaTime) {
	Entity::Update(deltaTime);

	UpdateViewMatrix();
	m_renderer->UpdateMVP();

	UpdateFrustrumPlanes();

	//CheckForMovementInput(deltaTime);
	//CheckForRotationInput(deltaTime);

	m_currentlyVisibleEntities = m_entities;
	for (int i = 0; i < m_currentlyVisibleEntities.size(); i++) {
		Entity* entity = m_currentlyVisibleEntities[i];

		entity->SetVisible(false);
		bool isBehindBsp = false;
		for (int j = 0; j < m_bspPlanes.size(); j++) {
			if (isBehindBSPPlane(entity, m_bspPlanes[j])) {
				isBehindBsp = true;
			}
		}
		if (!isBehindBsp)
			TestForVisibility(entity, i);
	}

	m_currentlyVisibleEntities.clear();
	for (int i = 0; i < m_entities.size(); i++) {
		Entity* currentEntity = (Entity*)m_entities[i];
		if (currentEntity->isVisible())
			m_currentlyVisibleEntities.push_back(currentEntity);
	}

	if (m_currentlyVisibleEntities != m_previouslyVisibleEntities) {
		m_previouslyVisibleEntities = m_currentlyVisibleEntities;

		printf("\nVisible entities:\n");

		for (int i = 0; i < m_currentlyVisibleEntities.size(); i++) {
			printf("- %s\n", m_currentlyVisibleEntities[i]->GetName());
		}
	}

	m_renderer->LoadIdentityMatrix();
}

void Camera::UpdateViewMatrix() {
	m_ViewMat = glm::lookAt(
		m_transform->GetPosition(),
		m_transform->GetPosition() + m_transform->foward,
		m_transform->up
	);
	m_renderer->SetCamView(m_ViewMat);
}

void Camera::CheckForMovementInput(float deltaTime) {
	float movementSpeed = m_strafeSpeed * deltaTime;
	GLFWwindow* window = (GLFWwindow*)m_Window->GetWindowPtr();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // Move forward
		m_transform->Walk(movementSpeed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // Move backward
		m_transform->Walk(-movementSpeed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // Strafe right
		m_transform->Strafe(movementSpeed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // Strafe left
		m_transform->Strafe(-movementSpeed);
}

void Camera::CheckForRotationInput(float deltaTime) {
	GLFWwindow* window = (GLFWwindow*)m_Window->GetWindowPtr();

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		m_transform->Yaw(-m_RotationSpeed * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		m_transform->Yaw(m_RotationSpeed * deltaTime);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		m_transform->Pitch(-m_RotationSpeed * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		m_transform->Pitch(m_RotationSpeed * deltaTime);

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		m_transform->Roll(m_RotationSpeed * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		m_transform->Roll(-m_RotationSpeed * deltaTime);
}

void Camera::UpdateFrustrumPlanes() {
	glm::mat4 mvp = m_renderer->GetMVP();

	m_frustrumPlanes[ClippingPlane::Far].a = mvp[0][3] - mvp[0][2];
	m_frustrumPlanes[ClippingPlane::Far].b = mvp[1][3] - mvp[1][2];
	m_frustrumPlanes[ClippingPlane::Far].c = mvp[2][3] - mvp[2][2];
	m_frustrumPlanes[ClippingPlane::Far].d = mvp[3][3] - mvp[3][2];
	m_frustrumPlanes[ClippingPlane::Far].NormalizePlane();

	m_frustrumPlanes[ClippingPlane::Near].a = mvp[0][3] + mvp[0][2];
	m_frustrumPlanes[ClippingPlane::Near].b = mvp[1][3] + mvp[1][2];
	m_frustrumPlanes[ClippingPlane::Near].c = mvp[2][3] + mvp[2][2];
	m_frustrumPlanes[ClippingPlane::Near].d = mvp[3][3] + mvp[3][2];
	m_frustrumPlanes[ClippingPlane::Near].NormalizePlane();

	m_frustrumPlanes[ClippingPlane::Left].a = mvp[0][3] + mvp[0][0];
	m_frustrumPlanes[ClippingPlane::Left].b = mvp[1][3] + mvp[1][0];
	m_frustrumPlanes[ClippingPlane::Left].c = mvp[2][3] + mvp[2][0];
	m_frustrumPlanes[ClippingPlane::Left].d = mvp[3][3] + mvp[3][0];
	m_frustrumPlanes[ClippingPlane::Left].NormalizePlane();

	m_frustrumPlanes[ClippingPlane::Right].a = mvp[0][3] - mvp[0][0];
	m_frustrumPlanes[ClippingPlane::Right].b = mvp[1][3] - mvp[1][0];
	m_frustrumPlanes[ClippingPlane::Right].c = mvp[2][3] - mvp[2][0];
	m_frustrumPlanes[ClippingPlane::Right].d = mvp[3][3] - mvp[3][0];
	m_frustrumPlanes[ClippingPlane::Right].NormalizePlane();

	m_frustrumPlanes[ClippingPlane::Top].a = mvp[0][3] - mvp[0][1];
	m_frustrumPlanes[ClippingPlane::Top].b = mvp[1][3] - mvp[1][1];
	m_frustrumPlanes[ClippingPlane::Top].c = mvp[2][3] - mvp[2][1];
	m_frustrumPlanes[ClippingPlane::Top].d = mvp[3][3] - mvp[3][1];
	m_frustrumPlanes[ClippingPlane::Top].NormalizePlane();

	m_frustrumPlanes[ClippingPlane::Bottom].a = mvp[0][3] + mvp[0][1];
	m_frustrumPlanes[ClippingPlane::Bottom].b = mvp[1][3] + mvp[1][1];
	m_frustrumPlanes[ClippingPlane::Bottom].c = mvp[2][3] + mvp[2][1];
	m_frustrumPlanes[ClippingPlane::Bottom].d = mvp[3][3] + mvp[3][1];
	m_frustrumPlanes[ClippingPlane::Bottom].NormalizePlane();
}

void Camera::TestForVisibility(Entity* entity, int index) {

	entity->SetVisible(false);

	if (isInsideFrustrum(m_frustrumPlanes[ClippingPlane::Far], entity)) {
		//printf("\nEntity %s is behind plane_far\n", entity->GetName());
		m_currentlyVisibleEntities.erase(m_currentlyVisibleEntities.begin() + index);
		return;
	}
	if (isInsideFrustrum(m_frustrumPlanes[ClippingPlane::Near], entity)) {
		//printf("\nEntity %s is behind plane_near\n", entity->GetName());
		m_currentlyVisibleEntities.erase(m_currentlyVisibleEntities.begin() + index);
		return;
	}
	if (isInsideFrustrum(m_frustrumPlanes[ClippingPlane::Left], entity)) {
		//printf("\nEntity %s is behind plane_left\n", entity->GetName());
		m_currentlyVisibleEntities.erase(m_currentlyVisibleEntities.begin() + index);
		return;
	}
	if (isInsideFrustrum(m_frustrumPlanes[ClippingPlane::Right], entity)) {
		//printf("\nEntity %s is behind plane_right\n", entity->GetName());
		m_currentlyVisibleEntities.erase(m_currentlyVisibleEntities.begin() + index);
		return;
	}
	if (isInsideFrustrum(m_frustrumPlanes[ClippingPlane::Top], entity)) {
		//printf("\nEntity %s is behind plane_top\n", entity->GetName());
		m_currentlyVisibleEntities.erase(m_currentlyVisibleEntities.begin() + index);
		return;
	}
	if (isInsideFrustrum(m_frustrumPlanes[ClippingPlane::Bottom], entity)) {
		//printf("\nEntity %s is behind plane_bottom\n", entity->GetName());
		m_currentlyVisibleEntities.erase(m_currentlyVisibleEntities.begin() + index);
		return;
	}
	entity->SetVisible(true);

	//for (int i = 0; i < entity->GetChildren().size(); i++) {
	//	TestForVisibility((Entity*)entity->GetChildren()[i], index);
	//}
}

bool Camera::isInsideFrustrum(Plane& plane, Entity* entity) {
	BoundingBox* entityBoundingBox = entity->GetTransform()->GetBoundingBox();
	for (int vertexId = 0; vertexId < entityBoundingBox->vertices.size(); vertexId++) {
		glm::vec3 boundingBoxVertex = entityBoundingBox->vertices[vertexId];
		float dist = plane.a * boundingBoxVertex.x + plane.b * boundingBoxVertex.y + plane.c * boundingBoxVertex.z + plane.d;
	
		if (dist >= 0) return false;
	}
	return true;
}

bool Camera::isBehindBSPPlane(const Entity* entity, const Plane& bspPlane) const {
	float cameraDistanceSign = glm::sign(bspPlane.SignedDistanceToPlane(bspPlane, m_transform->GetPosition()));

	BoundingBox* entityBoundingBox = entity->GetTransform()->GetBoundingBox();
	for (int vertexId = 0; vertexId < entityBoundingBox->vertices.size(); vertexId++) {
		glm::vec3 vertexPosition = entityBoundingBox->vertices[vertexId];
		float vertexDistanceSign = glm::sign(bspPlane.SignedDistanceToPlane(bspPlane, vertexPosition));

		if (vertexDistanceSign == cameraDistanceSign) return false;
	}
	return true;
}

#include "Camera.h"
#include "Transform.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

Camera::Camera(Renderer* renderer, Window* window) : Entity(renderer) {
	m_Window = window;

	m_CameraTarget = glm::vec3(0, 0, 0);
	m_strafeSpeed = 5.0f;
	m_RotationSpeed = 100.0f;
	m_transform->Yaw(180);

	UpdateViewMatrix();

	zNear = 0.1f;
	zFar = 10.0f;
	fov = 45;
	aspectRatio = (float)m_Window->GetWidth() / (float)m_Window->GetHeight();

	m_renderer->SetPerpectiveCam(fov, aspectRatio, zNear, zFar);
}

void Camera::Update(float deltaTime) {
	UpdateViewMatrix();
	CheckForMovementInput(deltaTime);
	CheckForRotationInput(deltaTime);
	UpdateClippingPlanes();

	Entity::Update(deltaTime);
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

void Camera::UpdateViewMatrix() {
	m_ViewMat = glm::lookAt(
		m_transform->GetPosition(),
		m_transform->GetPosition() + m_transform->foward,
		m_transform->up
	);
	m_renderer->SetCamView(m_ViewMat);
}

void Camera::UpdateClippingPlanes() {
	float nearWidth = 4 / 2;
	float nearHeight = 3 / 2;

	plane_near.bottomLeft = m_transform->GetPosition() + m_transform->right * -nearWidth + m_transform->up * -nearHeight;
	plane_near.bottomRight = m_transform->GetPosition() + m_transform->right * nearWidth + m_transform->up * -nearHeight;
	plane_near.topRight = m_transform->GetPosition() + m_transform->right * nearWidth + m_transform->up * nearHeight;
	plane_near.topLeft = m_transform->GetPosition() + m_transform->right * -nearWidth + m_transform->up * nearHeight;
	plane_near.normal = GetTransform()->foward;

	//printf("\nProjected foward vector: %f, %f, %f \n", projectedFoward.x, projectedFoward.y, projectedFoward.z);
	glm::vec3 projectedFoward = GetTransform()->foward * zFar;
	projectedFoward.x -= glm::cos(glm::radians(fov)) * zFar;
	projectedFoward.y += glm::cos(glm::radians(fov)) * zFar;
	plane_far.bottomLeft = GetTransform()->GetPosition() + projectedFoward + GetTransform()->right * -nearWidth + GetTransform()->up * -nearHeight;

	projectedFoward = GetTransform()->foward * zFar;
	projectedFoward.x += glm::cos(glm::radians(fov)) * zFar;
	projectedFoward.y -= glm::cos(glm::radians(fov)) * zFar;
	plane_far.bottomRight = GetTransform()->GetPosition() + GetTransform()->foward * zFar + GetTransform()->right * nearWidth + GetTransform()->up * -nearHeight;

	projectedFoward = GetTransform()->foward * zFar;
	projectedFoward.x += glm::cos(glm::radians(fov)) * zFar;
	projectedFoward.y += glm::cos(glm::radians(fov)) * zFar;
	plane_far.topRight = GetTransform()->GetPosition() + GetTransform()->foward * zFar + GetTransform()->right * nearWidth + GetTransform()->up * nearHeight;

	projectedFoward = GetTransform()->foward * zFar;
	projectedFoward.x -= glm::cos(glm::radians(fov)) * zFar;
	projectedFoward.y += glm::cos(glm::radians(fov)) * zFar;
	plane_far.topLeft = GetTransform()->GetPosition() + GetTransform()->foward * zFar + GetTransform()->right * -nearWidth + GetTransform()->up * nearHeight;
	plane_far.normal = -GetTransform()->foward;

	plane_left.bottomLeft = plane_far.bottomLeft;
	plane_left.normal = glm::normalize(glm::cross(plane_far.bottomLeft - plane_near.bottomLeft, World::up));

	plane_right.bottomLeft = plane_near.bottomRight;
	plane_right.normal = glm::normalize(glm::cross(plane_near.bottomRight - plane_far.bottomRight, World::up));

	plane_top.bottomLeft = plane_near.topLeft;
	plane_top.normal = glm::normalize(glm::cross(plane_far.topRight - plane_near.topRight, World::right));

	plane_bottom.bottomLeft = plane_near.bottomLeft;
	plane_bottom.normal = glm::normalize(glm::cross(plane_near.bottomRight - plane_far.bottomRight, World::right));
}

void Camera::TestForFrustrumCulling(Entity* entity) {
	entity->SetIsInsideFrustrum(false);
	if (isBehindPlane(plane_far, entity)) {
		printf("\nEntity %s is behind plane_far\n", entity->GetName());
		return;
	}
	if (isBehindPlane(plane_near, entity)) {
		printf("\nEntity %s is behind plane_near\n", entity->GetName());
		return;
	}
	if (isBehindPlane(plane_left, entity)) {
		printf("\nEntity %s is behind plane_left\n", entity->GetName());
		return;
	}
	if (isBehindPlane(plane_right, entity)) {
		printf("\nEntity %s is behind plane_right\n", entity->GetName());
		return;
	}
	if (isBehindPlane(plane_top, entity)) {
		printf("\nEntity %s is behind plane_top\n", entity->GetName());
		return;
	}
	if (isBehindPlane(plane_bottom, entity)) {
		printf("\nEntity %s is behind plane_bottom\n", entity->GetName());
		return;
	}
	entity->SetIsInsideFrustrum(true);
}

bool Camera::isBehindPlane(Plane plane, Entity* entity) const {
	BoundingBox entityBB = entity->GetTransform()->GetboundingBox();
	for (int i = 0; i < entityBB.vertices.size(); i++) {
		if (glm::dot(entityBB.vertices[i] - plane.bottomLeft, plane.normal) > 0)
			return false;
	}
	return true;
}

void Camera::DrawFrustrumPlanes() {
	//m_renderer->DrawSquare(
	//	m_clippingPlanes.near.bottomLeft,
	//	m_clippingPlanes.near.bottomRight,
	//	m_clippingPlanes.near.topRight,
	//	m_clippingPlanes.near.topLeft
	//);
}
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
	zFar = 20.0f;
	fov = 45;
	aspectRatio = (float)m_Window->GetWidth() / (float)m_Window->GetHeight();

	m_renderer->SetPerpectiveCam(fov, aspectRatio, zNear, zFar);

}

void Camera::UpdateFrustrumPlanes() {
	glm::mat4 comboMatrix = m_renderer->GetViewMat();

	// Left clipping plane
	m_planes[ClippingPlane::Left].a = comboMatrix[3][0] + comboMatrix[0][0];
	m_planes[ClippingPlane::Left].b = comboMatrix[3][1] + comboMatrix[0][1];
	m_planes[ClippingPlane::Left].c = comboMatrix[3][2] + comboMatrix[0][2];
	m_planes[ClippingPlane::Left].d = comboMatrix[3][3] + comboMatrix[0][3];

	// Right clipping plane
	m_planes[ClippingPlane::Right].a = comboMatrix[3][0] - comboMatrix[0][0];
	m_planes[ClippingPlane::Right].b = comboMatrix[3][1] - comboMatrix[0][1];
	m_planes[ClippingPlane::Right].c = comboMatrix[3][2] - comboMatrix[0][2];
	m_planes[ClippingPlane::Right].d = comboMatrix[3][3] - comboMatrix[0][3];

	// Top clipping plane
	m_planes[ClippingPlane::Top].a = comboMatrix[3][0] - comboMatrix[1][0];
	m_planes[ClippingPlane::Top].b = comboMatrix[3][1] - comboMatrix[1][1];
	m_planes[ClippingPlane::Top].c = comboMatrix[3][2] - comboMatrix[1][2];
	m_planes[ClippingPlane::Top].d = comboMatrix[3][3] - comboMatrix[1][3];

	// Bottom clipping plane
	m_planes[ClippingPlane::Bottom].a = comboMatrix[3][0] + comboMatrix[1][0];
	m_planes[ClippingPlane::Bottom].b = comboMatrix[3][1] + comboMatrix[1][1];
	m_planes[ClippingPlane::Bottom].c = comboMatrix[3][2] + comboMatrix[1][2];
	m_planes[ClippingPlane::Bottom].b = comboMatrix[3][3] + comboMatrix[1][3];

	// Near clipping plane
	m_planes[ClippingPlane::Near].a = comboMatrix[3][0] + comboMatrix[2][0];
	m_planes[ClippingPlane::Near].b = comboMatrix[3][1] + comboMatrix[2][1];
	m_planes[ClippingPlane::Near].c = comboMatrix[3][2] + comboMatrix[2][2];
	m_planes[ClippingPlane::Near].d = comboMatrix[3][3] + comboMatrix[2][3];

	// Far clipping plane
	m_planes[ClippingPlane::Far].a = comboMatrix[3][0] - comboMatrix[2][0];
	m_planes[ClippingPlane::Far].b = comboMatrix[3][1] - comboMatrix[2][1];
	m_planes[ClippingPlane::Far].c = comboMatrix[3][2] - comboMatrix[2][2];
	m_planes[ClippingPlane::Far].d = comboMatrix[3][3] - comboMatrix[2][3];

	//printf("\nFar plane values: a = %f, b = %f, c = %f, d = %f\n",
	//	m_planes[ClippingPlane::Far].a,
	//	m_planes[ClippingPlane::Far].b,
	//	m_planes[ClippingPlane::Far].c,
	//	m_planes[ClippingPlane::Far].d
	//);
	//
	//printf("\nNear plane values: a = %f, b = %f, c = %f, d = %f\n",
	//	m_planes[ClippingPlane::Near].a,
	//	m_planes[ClippingPlane::Near].b,
	//	m_planes[ClippingPlane::Near].c,
	//	m_planes[ClippingPlane::Near].d
	//);
	//
	//printf("\nRight plane values: a = %f, b = %f, c = %f, d = %f\n",
	//	m_planes[ClippingPlane::Right].a,
	//	m_planes[ClippingPlane::Right].b,
	//	m_planes[ClippingPlane::Right].c,
	//	m_planes[ClippingPlane::Right].d
	//);
}

void Camera::Update(float deltaTime) {
	UpdateViewMatrix();
	CheckForMovementInput(deltaTime);
	CheckForRotationInput(deltaTime);
	UpdateFrustrumPlanes();

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

void Camera::TestForFrustrumCulling(Entity* entity) {
	//for (int i = 0; i < entity->GetChildren().size(); i++) {
	//	TestForFrustrumCulling((Entity*)entity->GetChildren()[i]);
	//}

	entity->SetIsInsideFrustrum(false);
	if (isBehindPlane(m_planes[ClippingPlane::Far], entity)) {
		printf("\nEntity %s is behind plane_far\n", entity->GetName());
		return;
	}
	if (isBehindPlane(m_planes[ClippingPlane::Near], entity)) {
		printf("\nEntity %s is behind plane_near\n", entity->GetName());
		return;
	}
	//if (isBehindPlane(plane_left, entity)) {
	//	printf("\nEntity %s is behind plane_left\n", entity->GetName());
	//	return;
	//}
	//if (isBehindPlane(plane_right, entity)) {
	//	printf("\nEntity %s is behind plane_right\n", entity->GetName());
	//	return;
	//}
	//if (isBehindPlane(plane_top, entity)) {
	//	printf("\nEntity %s is behind plane_top\n", entity->GetName());
	//	return;
	//}
	//if (isBehindPlane(plane_bottom, entity)) {
	//	printf("\nEntity %s is behind plane_bottom\n", entity->GetName());
	//	return;
	//}
	entity->SetIsInsideFrustrum(true);
}

bool Camera::isBehindPlane(Plane& plane, Entity* entity) {
	//BoundingBox entityBB = entity->GetTransform()->GetboundingBox();
	//for (int i = 0; i < entityBB.vertices.size(); i++) {
	//	if (glm::dot(entityBB.vertices[i] - plane.bottomLeft, plane.normal) > 0)
	//		return false;
	//}

	BoundingBox entityBB = entity->GetTransform()->GetboundingBox();
	for (int i = 0; i < entityBB.vertices.size(); i++) {

		// TODO: figure out what the fuck is goinf on with the planes
		NormalizePlane(plane);
		float dot = plane.a * entityBB.vertices[i].x + plane.b * entityBB.vertices[i].y + plane.c * entityBB.vertices[i].z;

		printf("\nDot result: %f\n", dot);
		if (dot > 0) return false;
	}
	return true;
}

void Camera::NormalizePlane(Plane& plane) {
	float Distance = sqrtf(plane.a * plane.a + plane.b * plane.b + plane.c * plane.c);
	plane.a = plane.a / Distance;
	plane.b = plane.b / Distance;
	plane.c = plane.c / Distance;
	plane.d = plane.d / Distance;
}

void Camera::DrawFrustrumPlanes() {
	//m_renderer->DrawSquare(
	//	m_clippingPlanes.near.bottomLeft,
	//	m_clippingPlanes.near.bottomRight,
	//	m_clippingPlanes.near.topRight,
	//	m_clippingPlanes.near.topLeft
	//);
}
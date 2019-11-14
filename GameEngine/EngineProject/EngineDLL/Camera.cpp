#include "Camera.h"
#include "Transform.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

Camera::Camera(Renderer* renderer, Window* window) : Entity(renderer) {
	SetName("Camera");

	m_Window = window;

	m_CameraTarget = glm::vec3(0, 0, 0);
	m_strafeSpeed = 5.0f;
	m_RotationSpeed = 100.0f;
	m_transform->Yaw(180);

	zNear = 0.1f;
	zFar = 20.0f;
	fov = 45;
	aspectRatio = (float)m_Window->GetWidth() / (float)m_Window->GetHeight();

	m_renderer->SetPerpectiveCam(fov, aspectRatio, zNear, zFar);

	UpdateViewMatrix();
}

void Camera::Update(float deltaTime) {
	Entity::Update(deltaTime);

	CheckForMovementInput(deltaTime);
	CheckForRotationInput(deltaTime);

	UpdateViewMatrix();
	m_renderer->SetPerpectiveCam(fov, aspectRatio, zNear, zFar);
	m_renderer->UpdateModelMatrix(m_transform->GetWorldMatrix());
	
	m_renderer->UpdateMVP();

	UpdateFrustrumPlanes();
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
	glm::mat4x4 mvp = m_renderer->GetMVP();

	m_planes[ClippingPlane::Far].a = mvp[0][3] - mvp[0][2];
	m_planes[ClippingPlane::Far].b = mvp[1][3] - mvp[1][2];
	m_planes[ClippingPlane::Far].c = mvp[2][3] - mvp[2][2];
	m_planes[ClippingPlane::Far].d = mvp[3][3] - mvp[3][2];
	NormalizePlane(m_planes[ClippingPlane::Far]);

	m_planes[ClippingPlane::Near].a = mvp[0][3] + mvp[0][2];
	m_planes[ClippingPlane::Near].b = mvp[1][3] + mvp[1][2];
	m_planes[ClippingPlane::Near].c = mvp[2][3] + mvp[2][2];
	m_planes[ClippingPlane::Near].d = mvp[3][3] + mvp[3][2];
	NormalizePlane(m_planes[ClippingPlane::Near]);

	m_planes[ClippingPlane::Left].a = mvp[0][3] + mvp[0][0];
	m_planes[ClippingPlane::Left].b = mvp[1][3] + mvp[1][0];
	m_planes[ClippingPlane::Left].c = mvp[2][3] + mvp[2][0];
	m_planes[ClippingPlane::Left].d = mvp[3][3] + mvp[3][0];
	NormalizePlane(m_planes[ClippingPlane::Left]);

	m_planes[ClippingPlane::Right].a = mvp[0][3] - mvp[0][0];
	m_planes[ClippingPlane::Right].b = mvp[1][3] - mvp[1][0];
	m_planes[ClippingPlane::Right].c = mvp[2][3] - mvp[2][0];
	m_planes[ClippingPlane::Right].d = mvp[3][3] - mvp[3][0];
	NormalizePlane(m_planes[ClippingPlane::Right]);

	m_planes[ClippingPlane::Top].a = mvp[0][3] - mvp[0][1];
	m_planes[ClippingPlane::Top].b = mvp[1][3] - mvp[1][1];
	m_planes[ClippingPlane::Top].c = mvp[2][3] - mvp[2][1];
	m_planes[ClippingPlane::Top].d = mvp[3][3] - mvp[3][1];
	NormalizePlane(m_planes[ClippingPlane::Top]);

	m_planes[ClippingPlane::Bottom].a = mvp[0][3] + mvp[0][1];
	m_planes[ClippingPlane::Bottom].b = mvp[1][3] + mvp[1][1];
	m_planes[ClippingPlane::Bottom].c = mvp[2][3] + mvp[2][1];
	m_planes[ClippingPlane::Bottom].d = mvp[3][3] + mvp[3][1];
	NormalizePlane(m_planes[ClippingPlane::Bottom]);
}

Camera::Plane Camera::CreatePlaneFromPointAndNormal(const glm::vec3& point, const glm::vec3& normal) {
	Plane plane;
	plane.a = normal.x;
	plane.b = normal.y;
	plane.c = normal.z;
	plane.d = -glm::dot(normal, point);
	return plane;
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
	if (isBehindPlane(m_planes[ClippingPlane::Left], entity)) {
		printf("\nEntity %s is behind plane_left\n", entity->GetName());
		return;
	}
	if (isBehindPlane(m_planes[ClippingPlane::Right], entity)) {
		printf("\nEntity %s is behind plane_right\n", entity->GetName());
		return;
	}
	if (isBehindPlane(m_planes[ClippingPlane::Top], entity)) {
		printf("\nEntity %s is behind plane_top\n", entity->GetName());
		return;
	}
	if (isBehindPlane(m_planes[ClippingPlane::Bottom], entity)) {
		printf("\nEntity %s is behind plane_bottom\n", entity->GetName());
		return;
	}
	entity->SetIsInsideFrustrum(true);
}

bool Camera::isBehindPlane(Plane& plane, Entity* entity) {
	glm::vec3 entityPos = entity->GetTransform()->GetPosition();
	float dist = plane.a * entityPos.x + plane.b * entityPos.y + plane.c * entityPos.z + plane.d;

	if (dist <= 0) return true;
	
	return false;
}

void Camera::NormalizePlane(Plane& plane) {
	float Distance = sqrtf(plane.a * plane.a + plane.b * plane.b + plane.c * plane.c);
	plane.a /= Distance;
	plane.b /= Distance;
	plane.c /= Distance;
	plane.d /= Distance;
}

float Camera::SignedDistanceToPlane(const Plane& plane, const glm::vec3& point) const {
	return (plane.a * point.x + plane.b * point.y + plane.c * point.z + plane.d);
}

glm::vec3 Camera::ClosestPointOnPlaneFromPosition(const Plane& plane, const glm::vec3& position) const {
	glm::vec3 planeNormal = glm::vec3(plane.a, plane.b, plane.c);
	return (position - planeNormal * SignedDistanceToPlane(plane, position));
}

void Camera::DrawFrustrumPlanes() {
	//m_renderer->DrawSquare(
	//	m_clippingPlanes.near.bottomLeft,
	//	m_clippingPlanes.near.bottomRight,
	//	m_clippingPlanes.near.topRight,
	//	m_clippingPlanes.near.topLeft
	//);
}
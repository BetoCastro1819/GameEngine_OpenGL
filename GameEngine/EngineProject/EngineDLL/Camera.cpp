#include "Camera.h"



Camera::Camera(Renderer* renderer) {
	m_Renderer = renderer;

	m_Pos = glm::vec3(0, 0, -5);
	m_FocusPoint = glm::vec3(0);
	m_Head = glm::vec3(0, 1, 0); // Default head is UP

	m_Rot = glm::vec3(0);

	m_ViewMat = glm::lookAt(
		m_Pos,
		m_FocusPoint,
		m_Head
	);

	m_Renderer->SetCamView(m_ViewMat);

	CalculateUnitVectors();
}

Camera::Camera(Renderer* renderer, glm::vec3 worldPos, glm::vec3 lookAt, glm::vec3 head) {
	m_Renderer = renderer;

	m_Pos = worldPos;
	m_Head = head;

	m_ViewMat = glm::lookAt(worldPos, lookAt, head);

	CalculateUnitVectors();
}

Camera::~Camera() {
}

// Movement
void Camera::Walk(float speed) {
	m_Pos += m_Foward * speed;

	m_Renderer->SetCamView(
		m_Pos,
		m_FocusPoint,
		m_Head
	);
}
void Camera::Strafe(float speed) {
	m_Pos += m_Side * speed;

	m_FocusPoint = glm::vec3(m_Pos.x, m_Pos.y, m_Pos.z + 1);

	m_Renderer->SetCamView(
		m_Pos,
		m_FocusPoint,
		m_Head
	);
}

// Rotation
void Camera::Pitch(float angle) {
	m_RotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_Side);

	// ==============================================
	// It rotates around focusPoint position... I think....
	m_ViewMat *= m_RotationMat;
	m_Renderer->SetCamView(m_ViewMat);

	CalculateUnitVectors();
}

void Camera::Yaw(float angle) {

}
void Camera::Roll(float angle) {

}

void Camera::CalculateUnitVectors() {
	m_Foward = glm::normalize(m_Pos - m_FocusPoint);
	m_Side = glm::cross(m_Head, m_Foward);
	m_Head = glm::cross(m_Foward, m_Side);
	m_Foward = glm::cross(m_Head, m_Side);
}

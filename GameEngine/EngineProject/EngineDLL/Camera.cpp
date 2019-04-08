#include "Camera.h"



Camera::Camera(Renderer* renderer) {

	m_Renderer		= renderer;

	m_Pos			= glm::vec3(0, 0, -4);
	m_Rot			= glm::vec3(0);
	
	m_Right			= glm::vec3(1, 0, 0);
	m_Head			= glm::vec3(0, 1, 0);
	m_Foward		= glm::vec3(0, 0, 1);

	UpdateViewMatrix();
}

Camera::~Camera() {
}

// Movement
void Camera::Walk(float speed) {
	m_Pos += m_Foward * speed;
	UpdateViewMatrix();
}

void Camera::Strafe(float speed) {
	m_Pos += m_Right * speed;
	UpdateViewMatrix();
}

// Rotation
void Camera::Pitch(float angle) {

	// Generate new m_Head position based on "angle" provided
	glm::vec3 newHead;
	newHead.x = m_Head.x;
	newHead.y = m_Head.y * glm::cos(angle) - m_Head.z * glm::sin(angle);
	newHead.z = m_Head.y * glm::sin(angle) + m_Head.z * glm::cos(angle);

	m_Head = glm::normalize(newHead);

	// Recalculate Foward Vector
	m_Foward = glm::normalize(glm::cross(m_Head, m_Right));
	
	UpdateViewMatrix();
}

void Camera::Yaw(float angle) {

	// Generate new m_Head position based on "angle" provided
	glm::vec3 newFoward;
	newFoward.x = m_Foward.x * glm::cos(angle) + m_Foward.z * glm::sin(angle);
	newFoward.y = m_Foward.y;
	newFoward.z = -m_Foward.x * glm::sin(angle) + m_Foward.z * glm::cos(angle);

	m_Foward = glm::normalize(newFoward);

	// Recalculate Foward Vector
	m_Right = glm::normalize(glm::cross(m_Foward, m_Head));

	UpdateViewMatrix();
}

void Camera::Roll(float angle) {

	// Generate new m_Head position based on "angle" provided
	glm::vec3 newRight;
	newRight.x = m_Right.x * glm::cos(angle) - m_Right.y * glm::sin(angle);
	newRight.y = m_Right.x * glm::sin(angle) + m_Right.y * glm::cos(angle);
	newRight.z = m_Right.z;

	m_Right = glm::normalize(newRight);

	// Recalculate Foward Vector
	m_Head = glm::normalize(glm::cross(m_Right, m_Foward));

	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix() {
	m_Renderer->SetCamView(
		m_Pos,
		m_Pos + m_Foward,
		m_Head
	);
}
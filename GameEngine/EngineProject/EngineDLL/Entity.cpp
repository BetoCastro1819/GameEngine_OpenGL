#include "Entity.h"

Entity::Entity(Renderer* renderer)	 {
	m_renderer = renderer;

	// Default Unit Vectors orientations
	m_Foward		= World_Foward;
	m_Up			= World_Up;
	m_Right			= World_Right;

	// Init Transform Vectors
	m_Position		= glm::vec3(0.0f);
	m_Rotation		= glm::vec3(0.0f);
	m_Scale			= glm::vec3(1.0f);

	// Init Transform Matrices
	m_ModelMat		= glm::mat4(1.0f);
	m_TranslateMat	= glm::mat4(1.0f);
	m_RotateMat		= glm::mat4(1.0f);
	m_ScaleMat		= glm::mat4(1.0f);
}

Entity::~Entity() {
}

void Entity::SetPos(float x, float y, float z) {
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;

	m_TranslateMat = glm::translate(glm::mat4(1.0f), m_Position);
	UpdateModelMatrix();
}

void Entity::SetScale(float x, float y, float z) {
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;

	m_ScaleMat = glm::scale(glm::mat4(1.0f), m_Scale);
	UpdateModelMatrix();
}

void Entity::SetRotation(glm::vec3 axis, float angle) {
}

void Entity::SetRotation(float x, float y, float z) {
	m_Rotation.x = x;
	m_Rotation.y = y;
	m_Rotation.z = z;

	// RIGHT axis
	//m_RotateMat = glm::rotate(glm::mat4(1.0f), glm::radians(x), m_Right);

	// FOWARD axis
	m_RotateMat = glm::rotate(glm::mat4(1.0f), glm::radians(z), m_Foward);
	m_Right = glm::normalize(glm::cos(x) * m_Right);
	m_Up = glm::cross(m_Foward, m_Right);

	
	UpdateModelMatrix();
}


void Entity::SetRotX(float angle) {
	m_RotateMat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_Right);

	glm::vec3 newUp;
	newUp.x = m_Up.x;
	newUp.y = m_Up.y * glm::cos(angle) - m_Up.z * glm::sin(angle);
	newUp.z = m_Up.y * glm::sin(angle) + m_Up.z * glm::cos(angle);

	// GET REAL ANGLE SOMEDAY...
	//m_Rotation.x = glm::acos(glm::dot(m_Up, newUp));

	// Solution in the meantime
	m_Rotation.x = angle;

	// Recalculate unit vectors
	m_Up = glm::normalize(newUp);
	m_Foward = glm::cross(m_Right, m_Up);

	UpdateModelMatrix();
}

void Entity::SetRotY(float angle) {
	m_Rotation.y = angle;

	m_RotateMat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_Up);

	glm::vec3 newFoward;
	newFoward.x = m_Up.x * glm::cos(angle) + m_Up.z * glm::sin(angle);
	newFoward.y = m_Up.y;
	newFoward.z = -m_Up.x * glm::sin(angle) + m_Up.z * glm::cos(angle);

	// Recalculate unit vectors
	m_Foward = glm::normalize(newFoward);
	m_Right = glm::cross(m_Up, m_Foward);

	UpdateModelMatrix();
}

void Entity::SetRotZ(float angle) {
	m_Rotation.z = angle;

	m_RotateMat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_Foward);

	glm::vec3 newRight;
	newRight.x = m_Up.x * glm::cos(angle) - m_Up.y * glm::sin(angle);
	newRight.y = m_Up.x * glm::sin(angle) + m_Up.y * glm::cos(angle);
	newRight.z = m_Up.z;

	// GET REAL ANGLE SOMEDAY...
	//m_Rotation.x = glm::acos(glm::dot(m_Up, newUp));

	// Solution in the meantime
	m_Rotation.x = angle;

	// Recalculate unit vectors
	m_Right = glm::normalize(newRight);
	m_Up = glm::cross(m_Foward, m_Right);

	UpdateModelMatrix();
}

void Entity::UpdateModelMatrix() {
	m_ModelMat = m_TranslateMat * m_RotateMat * m_ScaleMat;
}

void Entity::RecalculateUnitVectors() {
	
}
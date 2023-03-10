#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(2.5f), m_MouseSensitivity(0.1f), m_Zoom(45.0f)
{
	m_Position = position;
	m_WorldUp = up;
	m_Yaw = yaw;
	m_Pitch = pitch;
	UpdateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	: m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(2.5f), m_MouseSensitivity(0.1f), m_Zoom(45.0f)
{
	m_Position = glm::vec3(posX, posY, posZ);
	m_WorldUp = glm::vec3(upX, upY, upZ);
	m_Yaw = yaw;
	m_Pitch = pitch;
	UpdateCameraVectors();
}

void Camera::KeyboardInput(CameraMovement direction, float deltaTime)
{
	float CameraSpeed = m_MovementSpeed * deltaTime;
	if (direction == FORWARD)	m_Position += m_Front * CameraSpeed;
	if (direction == BACKWARD)	m_Position -= m_Front * CameraSpeed;
	if (direction == LEFT)		m_Position -= m_Right * CameraSpeed;
	if (direction == RIGHT)		m_Position += m_Right * CameraSpeed;
}

void Camera::MouseMovementInput(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= m_MouseSensitivity;
	yoffset *= m_MouseSensitivity;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	if(constrainPitch)
	{
		if (m_Pitch >  89.0f) m_Pitch =  89.0f;
		if (m_Pitch < -89.0f) m_Pitch = -89.0f;
	}
	UpdateCameraVectors();
}

void Camera::MouseScrollInput(float yoffset)
{
	m_Zoom -= (float)yoffset;
	if (m_Zoom <  1.0f) m_Zoom = 1.0f;
	if (m_Zoom > 45.0f) m_Zoom = 45.0f;
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

	m_Front = glm::normalize(front);
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  // normalize the vectors.
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

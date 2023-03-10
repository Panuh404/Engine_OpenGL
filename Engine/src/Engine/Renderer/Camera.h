#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Quiet
{
	enum CameraMovement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	class Camera
	{
	public:
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

		// Input Handle
		void KeyboardInput(CameraMovement direction, float deltaTime);
		void MouseMovementInput(float xoffset, float yoffset, GLboolean constrainPitch = true);
		void MouseScrollInput(float yoffset);

		// Data Get/Set
		glm::mat4 GetViewMatrix() { return glm::lookAt(m_Position, m_Position + m_Front, m_Up); }
		float GetZoom() { return m_Zoom; }
		void SetMovementSpeed(float speed) { m_MovementSpeed = speed; }
		void SetMouseSensitivity(float speed) { m_MouseSensitivity = speed; }

	private:
		glm::vec3 m_Position, m_Front, m_Up, m_Right, m_WorldUp;	// Camera Attributes
		float m_Yaw, m_Pitch;										// Camera Angles
		float m_MovementSpeed, m_MouseSensitivity, m_Zoom;			// Camera Options

		void UpdateCameraVectors();
	};
}
#include "Camera.h"
#include <iostream>



Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	Update();
}

void Camera::KeyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		//std::cout << "W" << std::endl;
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
	if (keys[GLFW_KEY_Q])
	{
		position -= up * velocity;
	}
	if (keys[GLFW_KEY_E])
	{
		position += up * velocity;
	}
	if (keys[GLFW_KEY_P])
	{
		position = glm::vec3(0.0f, 0.0f, -1.0f);
		front = glm::vec3(0.0f, 0.0f, 0.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		Update();
	}


	if (keys[GLFW_KEY_ENTER])
	{
		std::cout << "Camera Y (Yaw): " << yaw << std::endl;
		std::cout << "Camera X (Pitch) " << pitch << std::endl;
		std::cout << "Position " << position.x << " " << position.y << " " << position.z << std::endl;
		std:: cout << "Front " << front.x << " " << front.y << " " << front.z << std::endl;
	}
}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange)
{
	if (GetLockCamera() == true) return;

	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	// If the camera isn't locked, then update the camera
	Update();
	
}

void Camera::SetLockCamera(bool status)
{
	lock_camera = status;
}

bool Camera::GetLockCamera()
{
	return lock_camera;
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::Update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


Camera::~Camera()
{
}

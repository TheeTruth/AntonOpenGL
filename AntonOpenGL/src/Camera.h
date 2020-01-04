#pragma once
#include <glew.h>
#include <glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>


class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void KeyControl(bool* keys, GLfloat deltaTime);
	void MouseControl(GLfloat xChange, GLfloat yChange);
	static void SetLockCamera(bool status);
	static bool GetLockCamera();
	glm::mat4 CalculateViewMatrix();
	//glm::mat4 calculateProjectionMatrix();

	~Camera();


private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	static bool lock_camera;
	GLfloat moveSpeed;
	GLfloat turnSpeed;
	void Update();
};


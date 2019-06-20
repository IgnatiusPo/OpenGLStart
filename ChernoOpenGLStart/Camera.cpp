#include "Camera.h"




Camera::Camera(glm::vec3 position /*= glm::vec3(0.0f, 0.0f, 0.0f)*/, 
	glm::vec3 front /*= glm::vec3(0.0f, -1.0f, 0.0f)*/, glm::vec3 up /*= glm::vec3(0.0f, 1.0f, 0.0f)*/, 
	float yaw /*= YAW*/, float pitch /*= PITCH*/, float sensitivity /*= 0.1f*/, float zoom /*= 45.f*/, float cameraSpeed /*= 2.5f*/)
	: _position(position), _forward(front), _worldUp(glm::normalize(up)), _yaw(yaw), _pitch(pitch), _sensitivity(sensitivity),_zoom(zoom), _cameraSpeed(cameraSpeed)
{
	UpdateCameraVectors();
}

void Camera::ProcessKeyboardInput(CameraMovement direction, float deltaTime)
{
	switch (direction)
	{
	case FORWARD:
		_position += _forward * _cameraSpeed * deltaTime;
		break;
	case BACKWARD:
		_position -= _forward * _cameraSpeed * deltaTime;
		break;
	case RIGHT:
		_position += _right * _cameraSpeed * deltaTime;
		break;
	case LEFT:
		_position -= _right * _cameraSpeed * deltaTime;
		break;
	}
}

void Camera::ProcessMouseInput(float xOffset, float yOffset)
{
	xOffset *= _sensitivity;
	yOffset *= _sensitivity;
	_yaw += xOffset;
	_pitch += yOffset;

	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;
	UpdateCameraVectors();
}

void Camera::ProcessScrollInput( float yOffset, float &fov)
{
	if (fov >= 1.0f && fov <= 45.f)
		fov -= yOffset;
	else if (fov <= 1.0f)
		fov = 1.0f;
	else if (fov >= 45.0f)
		fov = 45.f;
}

glm::mat4 Camera::GetViewMatrix()
{
	return myLookAt(_position, _position + _forward, _up);
}

void Camera::UpdateCameraVectors()
{
	//forward vector
	glm::vec3 front;
	front.x = cos(glm::radians(_pitch)) * cos(glm::radians(_yaw));
	front.y = sin(glm::radians(_pitch));
	front.z = cos(glm::radians(_pitch)) * sin(glm::radians(_yaw));
	_forward = glm::normalize(front);

	//right and up
	_right = glm::normalize(glm::cross(_forward, _worldUp));
	_up = glm::normalize(glm::cross(_right, _forward));

}

glm::mat4 myLookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up)
{
	glm::vec3 zAxis = glm::normalize(eye - center);
	glm::vec3 xAxis = glm::normalize(glm::cross(glm::normalize(up), zAxis));
	glm::vec3 yAxis = glm::cross(zAxis, xAxis);

	glm::mat4 matTranslation = glm::mat4(1.0f);
	// initialization Translation matrix
	matTranslation[3][0] = -eye.x;
	matTranslation[3][1] = -eye.y;
	matTranslation[3][2] = -eye.z;

	glm::mat4 matRotation = glm::mat4(1.0f);
	// initialization Rotation matrix
	matRotation[0][0] = xAxis.x;
	matRotation[0][1] = yAxis.x;
	matRotation[0][2] = zAxis.x;

	matRotation[1][0] = xAxis.y;
	matRotation[1][1] = yAxis.y;
	matRotation[1][2] = zAxis.y;

	matRotation[2][0] = xAxis.z;
	matRotation[2][1] = yAxis.z;
	matRotation[2][2] = zAxis.z;

	return matRotation * matTranslation;
}
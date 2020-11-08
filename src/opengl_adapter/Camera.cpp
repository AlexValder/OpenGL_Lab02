#include "Camera.h"
#include <iostream>

using namespace LAM;

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    :
      _position(position),
      _front(glm::vec3(0.0f, 0.0f, -1.0f)),
      _up(up),
      _movementSpeed(SPEED),
      _mouseSensitivity(SENSITIVITY),
      _zoom(ZOOM) {
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : _front(glm::vec3(0.0f, 0.0f, -1.0f)), _movementSpeed(SPEED), _mouseSensitivity(SENSITIVITY), _zoom(ZOOM),
      _position(glm::vec3(posX, posY, posZ)), _worldUp(glm::vec3(upX, upY, upZ)), _yaw(yaw), _pitch(pitch) {
    updateCameraVectors();
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(_position, _position + _front, _up);
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = _movementSpeed * deltaTime;
    switch (direction) {
    case CameraMovement::FORWARD:
        _position += _front * velocity;
        DebugPrint("Moved forward.");
        break;
    case CameraMovement::BACKWARD:
        _position -= _front * velocity;
        DebugPrint("Moved backward");
        break;
    case CameraMovement::LEFT:
        _position -= _right * velocity;
        DebugPrint("Moved left");
        break;
    case CameraMovement::RIGHT:
        _position += _right * velocity;
        DebugPrint("Moved right");
        break;
    }
}


void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= _mouseSensitivity;
    yoffset *= _mouseSensitivity;

    _yaw   += xoffset;
    _pitch += yoffset;

    if (constrainPitch)
    {
        if (_pitch > 89.0f) _pitch = 89.0f;
        if (_pitch < -89.0f) _pitch = -89.0f;
    }

    updateCameraVectors();
    DebugPrint("Mouse moved: %f %f", xoffset, yoffset);
}


void Camera::ProcessMouseScroll(float yoffset) {
    _zoom -= yoffset;
    if (_zoom < 1.0f) _zoom = 1.0f;
    if (_zoom > 45.0f) _zoom = 45.0f;
    DebugPrint("Mouse zoom: %f", _zoom);
}

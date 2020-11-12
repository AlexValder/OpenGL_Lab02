#include "Camera.h"
#include <iostream>

using namespace LAM;

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    :
      _position(position),
      _front(glm::vec3(0.f, 0.f, -1.f)),
      _up(glm::vec3(0.f, 1.f, 0.f)),
      _right(glm::vec3(1.f, 0.f, 0.f)),
      _movementSpeed(SPEED),
      _mouseSensitivity(SENSITIVITY),
      _zoom(ZOOM) {
    //updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : _front(glm::vec3(0.f, 0.f, -1.f)), _movementSpeed(SPEED), _mouseSensitivity(SENSITIVITY), _zoom(ZOOM),
      _position(glm::vec3(posX, posY, posZ)), _worldUp(glm::vec3(upX, upY, upZ)), _yaw(yaw), _pitch(pitch),
      _right(glm::vec3(1.f, 0.f, 0.f)) {
    //updateCameraVectors();
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(_position, _position + _front, _up);
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime) {
    _front = glm::normalize(_front);
    const auto velocity = _movementSpeed * deltaTime;
    switch (direction) {
    case CameraMovement::FORWARD:
        _position -= velocity * glm::vec3(0.f, 0.f, -1.f);
        DebugPrint("Velocity: %f", velocity);
        break;
    case CameraMovement::BACKWARD:
        _position += velocity * glm::vec3(0.f, 0.f, -1.f);
        DebugPrint("Velocity: %f", velocity);
        break;
    case CameraMovement::LEFT:
        _position -= glm::normalize(glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f))) * 1.f;
        break;
    case CameraMovement::RIGHT:
        _position += glm::normalize(glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f))) * 1.f;
        break;
    }
    DebugPrint("Position: %f, %f, %f", _position.x, _position.y, _position.z);
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

    //updateCameraVectors();
//    DebugPrint("Mouse moved: %f %f", xoffset, yoffset);
}


void Camera::ProcessMouseScroll(float yoffset) {
    _zoom -= yoffset * _mouseSensitivity;
    if (_zoom > 180.f) _zoom = 180.f;
    if (_zoom < 0.f) _zoom = 0.f;
}

#include "Camera.h"
#include <iostream>

using namespace LAM;

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    :
      _position(position),
      _front(glm::vec3(0.f, 0.f, -1.f)),
      _up(up),
      _worldUp(up),
      _right(glm::normalize(glm::cross(_front, _up))),
      _movementSpeed(SPEED),
      _mouseSensitivity(SENSITIVITY),
      _zoom(ZOOM) {
        UpdateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : _front(glm::vec3(0.f, 0.f, -1.f)), _up(glm::vec3(0.f, 1.f, 0.f)), _movementSpeed(SPEED), _mouseSensitivity(SENSITIVITY), _zoom(ZOOM),
      _position(glm::vec3(posX, posY, posZ)), _worldUp(glm::vec3(upX, upY, upZ)), _yaw(yaw), _pitch(pitch),
      _right(glm::normalize(glm::cross(_front, _up))) {
    UpdateCameraVectors();
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
        _position += velocity * _front;
        break;
    case CameraMovement::BACKWARD:
        _position -= velocity * _front;
        break;
    case CameraMovement::LEFT:
        _position -= glm::normalize(glm::cross(_front, _up)) * velocity;
        break;
    case CameraMovement::RIGHT:
        _position += glm::normalize(glm::cross(_front, _up)) * velocity;
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

    UpdateCameraVectors();
}


void Camera::ProcessMouseScroll(float yoffset) {
    _zoom -= yoffset * _mouseSensitivity;
    if (_zoom > 180.f) _zoom = 180.f;
    if (_zoom < 0.f) _zoom = 0.f;
}

void Camera::UpdateCameraVectors() noexcept {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    this->_front = glm::normalize(front);
    this->_right = glm::normalize(glm::cross(_front, _worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    this->_up    = glm::normalize(glm::cross(_right, _front));
    DebugPrint("UpdateCameraVectors: Position -> (%f, %f, %f), Front -> (%f, %f, %f), Up -> (%f, %f, %f), Right -> (%f, %f, %f)",
               _position.x, _position.y, _position.z,
               _front.x, _front.y, _front.z,
               _up.x, _up.y, _up.z,
               _right.x, _right.y, _right.z);
}

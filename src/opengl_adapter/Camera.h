#pragma once
#include "shared.h"
#include <iostream>

namespace LAM {

    enum class CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    // Default camera values
    constexpr float YAW         = -90.0f;
    constexpr float PITCH       =  0.0f;
    constexpr float SPEED       =  2.5f;
    constexpr float SENSITIVITY =  0.1f;
    constexpr float ZOOM        =  45.0f;

    class Camera final {
    public:
#define REGION REF GETTERS {
        auto& Position() {
            return _position;
        }

        auto& Front() {
            return _front;
        }

        auto& Up() {
            return _up;
        }

        auto& Right() {
            return _right;
        }

        auto& WorldUp() {
            return _worldUp;
        }

        auto& Yaw() {
            return _yaw;
        }

        auto& Pitch() {
            return _pitch;
        }

        auto& MovementSpeed() {
            return _movementSpeed;
        }

        auto& MouseSensitivity() {
            return _mouseSensitivity;
        }

        auto& Zoom() {
            return _zoom;
        }
#define ENDREGION REF GETTERS }

        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
               glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
               float yaw = YAW, float pitch = PITCH);

        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

        // returns the view matrix calculated using Euler Angles and the LookAt Matrix
        glm::mat4 GetViewMatrix() const;
        void ProcessKeyboard(CameraMovement direction, float deltaTime);
        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
        void ProcessMouseScroll(float yoffset);

    private:
        glm::vec3 _position;
        glm::vec3 _front;
        glm::vec3 _up;
        glm::vec3 _right;
        glm::vec3 _worldUp;
        // euler Angles
        float _yaw;
        float _pitch;
        // camera options
        float _movementSpeed;
        float _mouseSensitivity;
        float _zoom;

        void updateCameraVectors() {
            // calculate the new Front vector
            glm::vec3 front;
            front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
            front.y = sin(glm::radians(_pitch));
            front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
            _front = glm::normalize(_front);
            // also re-calculate the Right and Up vector
            _right = glm::normalize(glm::cross(_front, _worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            _up    = glm::normalize(glm::cross(_right, _front));
        }
    };
}

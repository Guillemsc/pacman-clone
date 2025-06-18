//
// Created by guillem on 6/15/25.
//

#include "Camera.h"

#include "Constants/MathConstants.h"

namespace GEngineCore
{
    Camera::Camera()
    {
        SetProjection(_projection);
    }

    void Camera::SetProjection(const CameraProjection projection)
    {
        _projection = projection;
    }

    void Camera::SetPosition(const glm::vec3 &position)
    {
        _position = position;
    }

    void Camera::SetRotation(const glm::quat &rotation)
    {
        _rotation = rotation;
    }

    void Camera::SetPrespectiveFov(const float fov)
    {
        _prespectiveFov = fov;
    }

    void Camera::SetOrthographicPlane(const float plane)
    {
        _orthographicPlane = plane;
    }

    glm::vec3 Camera::GetPosition() const
    {
        return _position;
    }

    glm::quat Camera::GetRotation() const
    {
        return _rotation;
    }

    glm::vec3 Camera::GetForwardDirection() const
    {
        return _rotation * MathConstants::FORWARD;
    }

    glm::vec3 Camera::GetUpDirection() const
    {
        return _rotation * MathConstants::UP;
    }

    glm::vec3 Camera::GetRightDirection() const
    {
        return _rotation * MathConstants::RIGHT;
    }

    ::Camera Camera::GetRawCamera() const
    {
        const glm::vec3 forward = GetForwardDirection();
        const glm::vec3 actualPosition = { _position.x, -_position.y, _position.z };
        const glm::vec3 actualForward = { forward.x, -forward.y, forward.z };


        const glm::vec3 lookAt = actualPosition - actualForward;
        const glm::vec3 up = GetUpDirection();

        ::Camera _rawCamera = {};
        _rawCamera.position = { actualPosition.x, actualPosition.y, actualPosition.z };
        _rawCamera.target = { lookAt.x, lookAt.y, lookAt.z  };
        _rawCamera.up = { up.x, up.y, up.z };
        _rawCamera.projection = _projection;

        if (_projection == CameraProjection::CAMERA_ORTHOGRAPHIC)
        {
            _rawCamera.fovy = -_orthographicPlane;
        }
        else
        {
            _rawCamera.fovy = -_prespectiveFov;
        }

        return _rawCamera;
    }
} // GEngineCore
//
// Created by guillem on 6/15/25.
//

#include "Camera.h"

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

    ::Camera Camera::GetRawCamera()
    {
        const glm::vec3 FORWARD = glm::vec3(0, 0, -1);  // -Z in right-handed OpenGL
        const glm::vec3 UP      = glm::vec3(0, 1,  0);  // +Y

        glm::vec3 lookAt = _rotation * FORWARD;
        glm::vec3 up     = _rotation * UP;

        ::Camera _rawCamera = {};
        _rawCamera.position = { _position.x, _position.y, _position.z };
        _rawCamera.target = { lookAt.x, lookAt.y, lookAt.z };
        _rawCamera.up = { up.x, up.y, up.z };
        _rawCamera.projection = _projection;

        if (_projection == CameraProjection::CAMERA_ORTHOGRAPHIC)
        {
            _rawCamera.fovy = _orthographicPlane;
        }
        else
        {
            _rawCamera.fovy = _prespectiveFov;
        }

        return _rawCamera;
    }
} // GEngineCore
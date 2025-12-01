//
// Created by guillem on 6/15/25.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "GEngine/Raylib/RaylibWrapper.h"

#include "glm/fwd.hpp"
#include "glm/vec3.hpp"
#include "glm/detail/type_quat.hpp"

namespace GEngine
{
    class GEngineCoreModules;

    class Camera
    {
        friend class CameraModule;

    public:
        explicit Camera(GEngineCoreModules* modules);

        void SetProjection(CameraProjection projection);
        void SetPosition(const glm::vec3& position);
        void SetRotation(const glm::quat& rotation);
        void SetPrespectiveFov(float fov);
        void SetOrthographicPlane(float plane);

        glm::vec3 GetPosition() const;
        glm::quat GetRotation() const;

        glm::vec3 GetForwardDirection() const;
        glm::vec3 GetUpDirection() const;
        glm::vec3 GetRightDirection() const;

        ::Camera GetRawCamera() const;

    private:
        GEngineCoreModules* const _modules = nullptr;

        glm::vec3 _position = glm::vec3(0, 0, -100);
        glm::quat _rotation = glm::identity<glm::quat>();
        CameraProjection _projection = CameraProjection::CAMERA_PERSPECTIVE;
        float _prespectiveFov = 45;
        float _orthographicPlane = 200;
    };
}

#endif //CAMERA_H

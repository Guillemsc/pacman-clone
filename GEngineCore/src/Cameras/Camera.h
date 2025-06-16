//
// Created by guillem on 6/15/25.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"

#include "glm/fwd.hpp"
#include "glm/vec3.hpp"
#include "glm/detail/type_quat.hpp"

namespace GEngineCore
{
    class Camera
    {
    public:
        Camera();

        void SetProjection(CameraProjection projection);

    private:
        ::Camera GetRawCamera();

    private:
        glm::vec3 _position = glm::vec3(0, 0, -100);
        glm::quat _rotation = glm::quat();
        CameraProjection _projection = CameraProjection::CAMERA_PERSPECTIVE;
        float _prespectiveFov = 45;
        float _orthographicPlane = -200;
    };
}

#endif //CAMERA_H

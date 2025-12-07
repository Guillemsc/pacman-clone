//
// Created by guillem on 12/7/25.
//

#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "GEngine/Tickables/Tickable.h"
#include "glm/vec2.hpp"

namespace PacMan
{
    class CameraData;

    class CameraManager final : public GEngine::Tickable
    {
    public:
        explicit CameraManager(CameraData* cameraData);

        void Tick() override;

        void SetBounds(const glm::i32vec2& bounds);

    private:
        CameraData* const _cameraData;

        glm::vec2 _bounds = glm::vec2(0);
    };
}

#endif //CAMERAMANAGER_H

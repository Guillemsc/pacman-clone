//
// Created by guillem on 12/7/25.
//

#include "CameraManager.h"

#include "GEngine/Components/Camera2dComponent.h"
#include "GEngine/Entities/Entity.h"
#include "PacMan/Shared/Camera/Data/CameraData.h"

namespace PacMan
{
    CameraManager::CameraManager(CameraData* cameraData)
        : _cameraData(cameraData)
    {

    }

    void CameraManager::Tick()
    {
        if (_bounds.x <= 0 || _bounds.y <= 0) return;

        const std::shared_ptr<GEngine::Entity> entity = _cameraData->CameraEntity.lock();
        if (!entity) return;

        const std::shared_ptr<GEngine::Camera2dComponent> camera = entity->GetComponent<GEngine::Camera2dComponent>().lock();
        if (!camera) return;

        camera->EncapsulateBounds(_bounds);
    }

    void CameraManager::SetBounds(const glm::i32vec2& bounds)
    {
        _bounds = bounds;
    }
}

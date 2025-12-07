//
// Created by guillem on 12/7/25.
//

#ifndef CAMERADATA_H
#define CAMERADATA_H
#include <memory>

namespace GEngine
{
    class Entity;
}

namespace PacMan
{
    class CameraData
    {
    public:
        std::weak_ptr<GEngine::Entity> CameraEntity;
    };
}

#endif //CAMERADATA_H

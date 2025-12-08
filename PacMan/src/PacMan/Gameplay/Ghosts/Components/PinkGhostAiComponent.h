//
// Created by guillem on 12/8/25.
//

#ifndef PINKGHOSTAICOMPONENT_H
#define PINKGHOSTAICOMPONENT_H

#include "GhostAiComponent.h"

namespace PacMan
{
    class PinkGhostAiComponent final : public GhostAiComponent
    {
        REGISTER_COMPONENT(PinkGhostAiComponent);

    public:
        explicit PinkGhostAiComponent(GEngine::GEngineCoreModules *modules, const std::weak_ptr<GEngine::Entity> &entity);

    protected:
        glm::i32vec2 GetChaseTargetGridPosition() const override;
        glm::i32vec2 GetHideTargetGridPosition() const override;

    };
}

#endif //PINKGHOSTAICOMPONENT_H

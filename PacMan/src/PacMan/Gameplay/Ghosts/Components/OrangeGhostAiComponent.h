//
// Created by guillem on 12/8/25.
//

#ifndef ORANGEGHOSTAICOMPONENT_H
#define ORANGEGHOSTAICOMPONENT_H

#include "GhostAiComponent.h"

namespace PacMan
{
    class OrangeGhostAiComponent final : public GhostAiComponent
    {
        REGISTER_COMPONENT(OrangeGhostAiComponent);

    public:
        explicit OrangeGhostAiComponent(GEngine::GEngineCoreModules *modules, const std::weak_ptr<GEngine::Entity> &entity);

    protected:
        glm::i32vec2 GetChaseTargetGridPosition() const override;
        glm::i32vec2 GetHideTargetGridPosition() const override;

    };
}

#endif //ORANGEGHOSTAICOMPONENT_H

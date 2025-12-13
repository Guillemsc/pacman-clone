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
        using GhostAiComponent::GhostAiComponent;

    protected:
        glm::i32vec2 GetChaseTargetGridPosition() const override;
        glm::i32vec2 GetScatterTargetGridPosition() const override;
    };
}

#endif //PINKGHOSTAICOMPONENT_H

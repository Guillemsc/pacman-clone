//
// Created by guillem on 12/8/25.
//

#ifndef CIANGHOSTAICOMPONENT_H
#define CIANGHOSTAICOMPONENT_H

#include "GhostAiComponent.h"

namespace PacMan
{
    class CianGhostAiComponent final : public GhostAiComponent
    {
        REGISTER_COMPONENT(CianGhostAiComponent);

    public:
        using GhostAiComponent::GhostAiComponent;

    protected:
        glm::i32vec2 GetChaseTargetGridPosition() const override;
        glm::i32vec2 GetScatterTargetGridPosition() const override;
        glm::i32vec2 GetFrightenedTargetGridPosition() const override;
    };
}

#endif //CIANGHOSTAICOMPONENT_H

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
        explicit CianGhostAiComponent(GEngine::GEngineCoreModules *modules, const std::weak_ptr<GEngine::Entity> &entity);

    protected:
        glm::i32vec2 GetChaseTargetGridPosition() const override;
        glm::i32vec2 GetHideTargetGridPosition() const override;

    };
}

#endif //CIANGHOSTAICOMPONENT_H

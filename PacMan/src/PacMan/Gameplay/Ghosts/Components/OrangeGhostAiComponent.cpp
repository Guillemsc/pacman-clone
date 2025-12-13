//
// Created by guillem on 12/8/25.
//

#include "OrangeGhostAiComponent.h"

#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"

namespace PacMan
{
    glm::i32vec2 OrangeGhostAiComponent::GetChaseTargetGridPosition() const
    {
        const std::shared_ptr<GEngine::Entity> player = _gameplayEntities->Player.lock();
        if (!player) return glm::i32vec2(0);

        const std::shared_ptr<MapMovementComponent> mapMovement = player->GetComponent<MapMovementComponent>().lock();

        return mapMovement->GetGridPosition();
    }

    glm::i32vec2 OrangeGhostAiComponent::GetScatterTargetGridPosition() const
    {
        return { -999, -999 };
    }
}

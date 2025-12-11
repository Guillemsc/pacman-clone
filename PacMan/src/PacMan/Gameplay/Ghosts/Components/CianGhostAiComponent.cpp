//
// Created by guillem on 12/8/25.
//

#include "CianGhostAiComponent.h"

#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"

namespace PacMan
{
    glm::i32vec2 CianGhostAiComponent::GetChaseTargetGridPosition() const
    {
        const std::shared_ptr<GEngine::Entity> player = _gameplayEntities->Player.lock();
        if (player == nullptr) return { 0, 0 };

        const std::shared_ptr<MapMovementComponent> mapMovement = player->GetComponent<MapMovementComponent>().lock();

        return mapMovement->GetGridPosition();
    }

    glm::i32vec2 CianGhostAiComponent::GetScatterTargetGridPosition() const
    {
        return { 999, -999 };
    }

    glm::i32vec2 CianGhostAiComponent::GetFrightenedTargetGridPosition() const
    {
        return { 0, 0 };
    }
}

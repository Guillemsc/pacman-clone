//
// Created by guillem on 12/8/25.
//

#include "PinkGhostAiComponent.h"

#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"

namespace PacMan
{
    glm::i32vec2 PinkGhostAiComponent::GetChaseTargetGridPosition() const
    {
        const std::shared_ptr<GEngine::Entity> player = _gameplayEntities->Player.lock();
        if (player == nullptr) return { 0, 0 };

        const std::shared_ptr<MapMovementComponent> mapMovement = player->GetComponent<MapMovementComponent>().lock();

        return mapMovement->GetGridPosition();
    }

    glm::i32vec2 PinkGhostAiComponent::GetScatterTargetGridPosition() const
    {
        return { -999, 999 };
    }

    glm::i32vec2 PinkGhostAiComponent::GetFrightenedTargetGridPosition() const
    {
        return { 0, 0 };
    }
}

//
// Created by guillem on 12/8/25.
//

#include "PinkGhostAiComponent.h"

#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"

namespace PacMan
{
    glm::i32vec2 PinkGhostAiComponent::GetChaseTargetGridPosition() const
    {
        const std::shared_ptr<GEngine::Entity> player = _gameplayEntities->Player.lock();
        if (!player) return glm::i32vec2(0);

        const std::shared_ptr<MapMovementComponent> mapMovement = player->GetComponent<MapMovementComponent>().lock();
        if (!mapMovement) return glm::i32vec2(0);

        const glm::i32vec2 directionVector = mapMovement->GetGridDirectionVector();

        const glm::i32vec2 targetPosition = mapMovement->GetGridPosition() + (directionVector * 3);

        return targetPosition;
    }

    glm::i32vec2 PinkGhostAiComponent::GetScatterTargetGridPosition() const
    {
        return { -999, 999 };
    }
}

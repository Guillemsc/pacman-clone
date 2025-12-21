//
// Created by guillem on 12/8/25.
//

#include "CianGhostAiComponent.h"

#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"

namespace PacMan
{
    glm::i32vec2 CianGhostAiComponent::GetChaseTargetGridPosition() const
    {
        const std::shared_ptr<GEngine::Entity> player = _gameplayEntities->Player.lock();
        if (!player) return glm::i32vec2(0);

        const std::shared_ptr<GEngine::Entity> mapGhost = _gameplayEntities->MapGhost.lock();
        if (!mapGhost) return glm::i32vec2(0);

        const std::shared_ptr<MapMovementComponent> playerMapMovement = player->GetComponent<MapMovementComponent>().lock();
        if (!playerMapMovement) return glm::i32vec2(0);

        const std::shared_ptr<MapMovementComponent> mapGhostMapMovement = mapGhost->GetComponent<MapMovementComponent>().lock();
        if (!mapGhostMapMovement) return glm::i32vec2(0);

        const glm::i32vec2 directionVector = playerMapMovement->GetGridDirectionVector();
        const glm::i32vec2 playerTargetPosition = playerMapMovement->GetGridPosition() + (directionVector * 2);

        const glm::i32vec2 distance = playerTargetPosition - mapGhostMapMovement->GetGridPosition();

        return playerTargetPosition + distance;
    }

    glm::i32vec2 CianGhostAiComponent::GetScatterTargetGridPosition() const
    {
        return { 999, -999 };
    }
}

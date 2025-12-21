//
// Created by guillem on 12/8/25.
//

#include "OrangeGhostAiComponent.h"

#include "GEngine/Components/TransformComponent.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"

namespace PacMan
{
    glm::i32vec2 OrangeGhostAiComponent::GetChaseTargetGridPosition() const
    {
        const std::shared_ptr<GEngine::Entity> player = _gameplayEntities->Player.lock();
        if (!player) return glm::i32vec2(0);

        const std::shared_ptr<GEngine::TransformComponent> playerTransform = player->GetTransform().lock();
        if (!playerTransform) return glm::i32vec2(0);

        const std::shared_ptr<GEngine::TransformComponent> ghostTransform = GetEntity().lock()->GetTransform().lock();
        if (!ghostTransform) return glm::i32vec2(0);

        const float distance = glm::distance(playerTransform->GetPositionXY(), ghostTransform->GetPositionXY());

        if (distance < 65)
        {
            return { -999, -999 };
        }

        const std::shared_ptr<MapMovementComponent> mapMovement = player->GetComponent<MapMovementComponent>().lock();

        return mapMovement->GetGridPosition();
    }

    glm::i32vec2 OrangeGhostAiComponent::GetScatterTargetGridPosition() const
    {
        return { -999, -999 };
    }
}

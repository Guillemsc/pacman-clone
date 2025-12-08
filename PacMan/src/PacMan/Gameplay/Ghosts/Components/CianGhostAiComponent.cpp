//
// Created by guillem on 12/8/25.
//

#include "CianGhostAiComponent.h"

#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"

namespace PacMan
{
    CianGhostAiComponent::CianGhostAiComponent(GEngine::GEngineCoreModules* modules, const std::weak_ptr<GEngine::Entity>& entity)
        : GhostAiComponent(modules, entity)
    {
    }

    glm::i32vec2 CianGhostAiComponent::GetChaseTargetGridPosition() const
    {
        const GameplayEntities* gameplayEntities = GEngine::ServiceLocator::Get<GameplayEntities>();

        const std::shared_ptr<GEngine::Entity> player = gameplayEntities->Player.lock();
        if (player == nullptr) return { 0, 0 };

        const std::shared_ptr<MapMovementComponent> mapMovement = player->GetComponent<MapMovementComponent>().lock();

        return mapMovement->GetGridPosition();
    }

    glm::i32vec2 CianGhostAiComponent::GetHideTargetGridPosition() const
    {
        return { 0, 0 };
    }
}

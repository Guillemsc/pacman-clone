//
// Created by guillem on 11/28/25.
//

#include "RedGhostAiComponent.h"

#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"

namespace PacMan
{
	glm::i32vec2 RedGhostAiComponent::GetChaseTargetGridPosition() const
	{
		const GameplayEntities* gameplayEntities = GEngine::ServiceLocator::Get<GameplayEntities>();

		const std::shared_ptr<GEngine::Entity> player = gameplayEntities->Player.lock();
		if (player == nullptr) return { 0, 0 };

		const std::shared_ptr<MapMovementComponent> mapMovement = player->GetComponent<MapMovementComponent>().lock();

		return mapMovement->GetGridPosition();
	}

	glm::i32vec2 RedGhostAiComponent::GetScatterTargetGridPosition() const
	{
		return { 999, 999 };
	}

	glm::i32vec2 RedGhostAiComponent::GetFrightenedTargetGridPosition() const
	{
		return { 0, 0 };
	}
}

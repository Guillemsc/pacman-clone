//
// Created by guillem on 11/28/25.
//

#include "RedGhostAiComponent.h"

#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"

namespace PacMan
{
	glm::i32vec2 RedGhostAiComponent::GetChaseTargetGridPosition() const
	{
		const std::shared_ptr<GEngine::Entity> player = _gameplayEntities->Player.lock();
		if (!player) return glm::i32vec2(0);

		const std::shared_ptr<MapMovementComponent> mapMovement = player->GetComponent<MapMovementComponent>().lock();

		return mapMovement->GetGridPosition();
	}

	glm::i32vec2 RedGhostAiComponent::GetScatterTargetGridPosition() const
	{
		return { 999, 999 };
	}
}

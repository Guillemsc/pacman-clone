//
// Created by guillem on 11/28/25.
//

#include "GhostAiComponent.h"

#include "glm/vec2.hpp"
#include "PacMan/Gameplay/Ghosts/Data/GhostsStateData.h"

namespace PacMan
{
	GhostAiComponent::GhostAiComponent(
		GEngine::GEngineCoreModules *modules,
		const std::weak_ptr<GEngine::Entity> &entity,
		GhostsStateData* ghostsStateData,
		const std::weak_ptr<MapMovementComponent>& mapMovementComponent
		)
		: Component(modules, entity),
		_ghostsStateData(ghostsStateData),
		_mapMovementComponent(mapMovementComponent)
	{
	}

	void GhostAiComponent::OnTick()
	{
		const std::shared_ptr<MapMovementComponent> mapMovement = _mapMovementComponent.lock();
		if (!mapMovement) return;

		glm::i32vec2 targetGridPosition;

		if (!_ghostsStateData->ghostsCanBeEaten)
		{
			targetGridPosition = GetChaseTargetGridPosition();
		}
		else
		{
			targetGridPosition = GetHideTargetGridPosition();
		}

		const bool targetChanged = targetGridPosition != _previousTargetGridPosition;

		if (targetChanged)
		{
			mapMovement->PathfindToGridPosition(targetGridPosition);
		}
	}
} // PacMan
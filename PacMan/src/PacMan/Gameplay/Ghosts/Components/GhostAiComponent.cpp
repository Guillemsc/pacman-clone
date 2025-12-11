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

		switch (_ghostsStateData->ghostsMode)
		{
			case GhostMode::CHASE:
			{
				targetGridPosition = GetChaseTargetGridPosition();
				break;
			}

			case GhostMode::SCATTER:
			{
				targetGridPosition = GetScatterTargetGridPosition();
				break;
			}

			case GhostMode::FRIGHTENED:
			{
				targetGridPosition = GetFrightenedTargetGridPosition();
				break;
			}
		}

		const bool targetChanged = targetGridPosition != _previousTargetGridPosition || !_hasValidPreviousTargetGridPosition;

		if (targetChanged)
		{
			const PathfindingResult pathfindingResult = mapMovement->PathfindToGridPosition(targetGridPosition);

			if (pathfindingResult.couldReachAnyPosition)
			{
				_previousTargetGridPosition = targetGridPosition;
				_validTargetGridPosition = pathfindingResult.realTargetGridPosition;
				_hasValidPreviousTargetGridPosition = true;
			}
		}
	}
} // PacMan
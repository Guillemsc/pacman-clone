//
// Created by guillem on 11/27/25.
//

#include "MapPathfindingSystem.h"

#include <optional>

#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Extensions/VectorExtensions.h"
#include "PacMan/Gameplay/MapMovement/Components/OldMapMovementComponent.h"
#include "PacMan/Gameplay/MapMovement/Components/MapPathfindingComponent.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapPathfindingManager.h"

namespace PacMan
{
	MapPathfindingSystem::MapPathfindingSystem(MapPathfindingManager *mapPathfindingManager, MapMovementManager* mapMovementManager)
		: _mapPathfindingManager(mapPathfindingManager), _mapMovementManager(mapMovementManager)
	{
	}

	void MapPathfindingSystem::Tick()
	{
		for (auto it = _components.begin(); it != _components.end();)
		{
			const std::shared_ptr<MapPathfindingComponent> component = it->lock();

			if (!component)
			{
				it = _components.erase(it);
				continue;
			}

			TickComponent(component);

			++it;
		}
	}

	void MapPathfindingSystem::Add(const std::weak_ptr<MapPathfindingComponent> &component)
	{
		_components.push_back(component);
	}

	void MapPathfindingSystem::TickComponent(const std::shared_ptr<MapPathfindingComponent> &component)
	{
		const std::shared_ptr<GEngine::Entity> entity = component->GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<OldMapMovementComponent> mapMovement = component->mapMovementComponent.lock();
		if (!mapMovement) return;

		if (!component->hasValidTargetGridPosition) return;

		const bool needsNewPath = component->targetGridPosition != component->pathTargetGridPosition;

		if (needsNewPath)
		{
			_mapPathfindingManager->GeneratePath(mapMovement->GridPosition, component->targetGridPosition, component->path);
			component->currentPathIndex = 0;
			component->pathTargetGridPosition = component->targetGridPosition;
		}

		glm::i32vec2 currentPathGridPosition = GEngine::VectorExtensions::GetOrDefault(
			component->path,
			component->currentPathIndex,
			mapMovement->TargetGridPosition
			);

		const glm::vec2 entityPosition = entity->GetTransform().lock()->GetPositionXY();
		const glm::vec2 currentPathPosition = _mapMovementManager->GridPositionToWorldPosition(currentPathGridPosition);

		const float distanceToCurrentPathPosition = glm::distance(entityPosition, currentPathPosition);
		const bool isCloseEnough = distanceToCurrentPathPosition < 0.6f;

		if (isCloseEnough)
		{
			++component->currentPathIndex;
			currentPathGridPosition = GEngine::VectorExtensions::GetOrDefault(
				component->path,
				component->currentPathIndex,
				mapMovement->GridPosition
				);
			mapMovement->NextDirection = GetDirectionFromOriginAndTargetGridPositions(mapMovement->TargetGridPosition, currentPathGridPosition);
		}
	}

	GEngine::CardinalDirection MapPathfindingSystem::GetDirectionFromOriginAndTargetGridPositions(
		const glm::i32vec2& origin,
		const glm::i32vec2& target
		)
	{
		if (origin.x < target.x)
		{
			return GEngine::CardinalDirection::RIGHT;
		}

		if (origin.x > target.x)
		{
			return GEngine::CardinalDirection::LEFT;
		}

		if (origin.y < target.y)
		{
			return GEngine::CardinalDirection::UP;
		}

		if (origin.y > target.y)
		{
			return GEngine::CardinalDirection::DOWN;
		}

		return GEngine::CardinalDirection::DOWN;
	}
}

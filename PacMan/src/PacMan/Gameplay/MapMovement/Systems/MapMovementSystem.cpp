//
// Created by guillem on 6/28/25.
//

#include "MapMovementSystem.h"

#include "GEngine/Components/TiledMap2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Extensions/CardinalDirectionExtensions.h"
#include "PacMan/Gameplay/MapMovement/Components/OldMapMovementComponent.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"

namespace PacMan
{
	MapMovementSystem::MapMovementSystem(MapMovementManager* mapMovementManager)
		: _mapMovementManager(mapMovementManager)
	{

	}

	void MapMovementSystem::Tick()
	{
		for (auto it = _components.begin(); it != _components.end();)
		{
			const std::shared_ptr<OldMapMovementComponent> component = it->lock();

			if (!component)
			{
				it = _components.erase(it);
				continue;
			}

			TickComponent(component);

			++it;
		}
	}

	void MapMovementSystem::Add(const std::weak_ptr<OldMapMovementComponent> &component)
	{
		_components.push_back(component);
	}

	void MapMovementSystem::TickComponent(const std::shared_ptr<OldMapMovementComponent>& component)
	{
		if(GEngine::CardinalDirectionExtensions::AreInverseDirections(component->Direction, component->NextDirection))
		{
			component->GridPosition = component->GridPosition + GEngine::CardinalDirectionExtensions::GetDirectionVector(component->Direction);
			component->Direction = component->NextDirection;
			component->ProgressToTarget = 1 - component->ProgressToTarget;
		}

		const glm::i32vec2 directionVector = GEngine::CardinalDirectionExtensions::GetDirectionVector(component->Direction);
		const glm::i32vec2 targetGridPosition = component->GridPosition + directionVector;

		const bool canMove = _mapMovementManager->IsWalkable(targetGridPosition);

		if (canMove)
		{
			component->TargetGridPosition = targetGridPosition;

			const glm::vec2 startWorldPosition = _mapMovementManager->GridPositionToWorldPosition(component->GridPosition);
			const glm::vec2 endWorldPosition = _mapMovementManager->GridPositionToWorldPosition(component->TargetGridPosition);

			component->ProgressToTarget += component->Speed;

			const glm::vec2 finalWorldPosition = GEngine::MathExtensions::Lerp(startWorldPosition, endWorldPosition, component->ProgressToTarget);

			component->GetEntity().lock()->GetTransform().lock()->SetPositionXY(finalWorldPosition);

			if (component->ProgressToTarget >= 1)
			{
				component->ProgressToTarget = component->ProgressToTarget - 1;
				component->GridPosition = component->TargetGridPosition;

				TryApplyNextDirection(
					_mapMovementManager,
					component.get(),
					component->NextDirection
				);

				component->GetEntity().lock()->GetTransform().lock()->SetPositionXY(endWorldPosition);
			}
		}
		else
		{
			TryApplyNextDirection(
				_mapMovementManager,
				component.get(),
				component->NextDirection
			);
		}
	}

	bool MapMovementSystem::TryApplyNextDirection(
		const MapMovementManager* mapMovementManager,
		OldMapMovementComponent *movementComponent,
		const GEngine::CardinalDirection direction

		)
	{
		const bool isValidNextDirection = IsValidNextDirection(
			mapMovementManager,
			movementComponent,
			direction
			);

		if (isValidNextDirection)
		{
			movementComponent->Direction = movementComponent->NextDirection;
		}

		return isValidNextDirection;
	}

	bool MapMovementSystem::IsValidNextDirection(
		const MapMovementManager* mapMovementManager,
		const OldMapMovementComponent *movementComponent,
		const GEngine::CardinalDirection direction
		)
	{
		const glm::i32vec2 directionVector = GEngine::CardinalDirectionExtensions::GetDirectionVector(direction);
		const glm::i32vec2 testingPosition = movementComponent->GridPosition + directionVector;

		const bool hasTile = mapMovementManager->IsWalkable(testingPosition);

		return hasTile;
	}
}

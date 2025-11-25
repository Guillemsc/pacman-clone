//
// Created by guillem on 6/28/25.
//

#include "MapMovementSystem.h"

#include "GEngine/Components/TiledMap2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Extensions/CardinalDirectionExtensions.h"
#include "../Components/MapMovementComponent.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"

namespace PacMan
{
	MapMovementSystem::MapMovementSystem(const std::weak_ptr<MapMovementManager> &mapMovementManager)
	{
		_mapMovementManagerPtr = mapMovementManager;
	}

	void MapMovementSystem::Tick()
	{
		const std::shared_ptr<MapMovementManager> tileMapComponent = _mapMovementManagerPtr.lock();

		for (auto it = _components.begin(); it != _components.end();)
		{
			const std::shared_ptr<MapMovementComponent> component = it->lock();

			if (!component)
			{
				it = _components.erase(it);
				continue;
			}

			if(GEngine::CardinalDirectionExtensions::AreInverseDirections(component->Direction, component->NextDirection))
			{
				component->GridPosition = component->GridPosition + GEngine::CardinalDirectionExtensions::GetDirectionVector(component->Direction);
				component->Direction = component->NextDirection;
				component->ProgressToTarget = 1 - component->ProgressToTarget;
			}

			glm::i32vec2 directionVector = GEngine::CardinalDirectionExtensions::GetDirectionVector(component->Direction);
			glm::i32vec2 targetGridPosition = component->GridPosition + directionVector;

			const bool canMove = tileMapComponent->IsWalkable(targetGridPosition);

			if (canMove)
			{
				glm::vec2 startWorldPosition = tileMapComponent->GridPositionToWorldPosition(component->GridPosition);
				glm::vec2 endWorldPosition = tileMapComponent->GridPositionToWorldPosition(targetGridPosition);

				component->ProgressToTarget += component->Speed;

				glm::vec2 finalWorldPosition = GEngine::MathExtensions::Lerp(startWorldPosition, endWorldPosition, component->ProgressToTarget);

				component->GetEntity().lock()->GetTransform().lock()->SetPositionXY(finalWorldPosition);

				if (component->ProgressToTarget >= 1)
				{
					component->ProgressToTarget = component->ProgressToTarget - 1;
					component->GridPosition = targetGridPosition;

					TryApplyNextDirection(
						tileMapComponent.get(),
						component.get(),
						component->NextDirection
					);

					component->GetEntity().lock()->GetTransform().lock()->SetPositionXY(endWorldPosition);
				}
			}
			else
			{
				TryApplyNextDirection(
					tileMapComponent.get(),
					component.get(),
					component->NextDirection
				);
			}

			++it;
		}
	}

	void MapMovementSystem::Add(const std::weak_ptr<MapMovementComponent> &component)
	{
		_components.push_back(component);
	}

	bool MapMovementSystem::TryApplyNextDirection(
		const MapMovementManager* mapMovementManager,
		MapMovementComponent *movementComponent,
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
		const MapMovementComponent *movementComponent,
		const GEngine::CardinalDirection direction
		)
	{
		const glm::i32vec2 directionVector = GEngine::CardinalDirectionExtensions::GetDirectionVector(direction);
		const glm::i32vec2 testingPosition = movementComponent->GridPosition + directionVector;

		const bool hasTile = mapMovementManager->IsWalkable(testingPosition);

		return hasTile;
	}
}

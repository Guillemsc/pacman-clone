//
// Created by guillem on 6/28/25.
//

#include "GridMovementSystem.h"

#include "GEngine/Components/TiledMap2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Extensions/CardinalDirectionExtensions.h"
#include "PacMan/Components/GridMovementComponent.h"

namespace PacMan
{
	GridMovementSystem::GridMovementSystem(const std::weak_ptr<GEngine::TiledMap2dRendererComponent> &tileMapComponent)
	{
		_tileMapComponentPtr = tileMapComponent;
	}

	void GridMovementSystem::Tick()
	{
		const std::shared_ptr<GEngine::TiledMap2dRendererComponent> tileMapComponent = _tileMapComponentPtr.lock();

		for (auto it = _components.begin(); it != _components.end();)
		{
			const std::shared_ptr<GridMovementComponent> component = it->lock();

			if (!component)
			{
				it = _components.erase(it);
				continue;
			}

			// if(Gengine::CardinalDirectionExtensions::AreInverseDirections(component->Direction, component->NextDirection))
			// {
			// 	component->GridPosition = component->GridPosition + Gengine::CardinalDirectionExtensions::GetDirectionVector(component->Direction);
			// 	component->Direction = component->NextDirection;
			// 	component->ProgressToTarget = 1 - component->ProgressToTarget;
			// }

			glm::i32vec2 directionVector = GEngine::CardinalDirectionExtensions::GetDirectionVector(component->Direction);
			glm::i32vec2 targetGridPosition = component->GridPosition + directionVector;

			const bool canMove = tileMapComponent->HasTileAtGridPosition(0, targetGridPosition);

			if (canMove)
			{
				glm::vec2 startWorldPosition = tileMapComponent->GridPositionToWorldPosition(0, component->GridPosition, GEngine::CellPosition::CENTER);
				glm::vec2 endWorldPosition = tileMapComponent->GridPositionToWorldPosition(0, targetGridPosition, GEngine::CellPosition::CENTER);

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

	void GridMovementSystem::Add(const std::weak_ptr<GridMovementComponent> &component)
	{
		_components.push_back(component);
	}

	void GridMovementSystem::TryApplyNextDirection(
		const GEngine::TiledMap2dRendererComponent* mapComponent,
		GridMovementComponent *movementComponent,
		const GEngine::CardinalDirection direction

		)
	{
		const bool isValidNextDirection = IsValidNextDirection(
			mapComponent,
			movementComponent,
			direction
			);

		if (isValidNextDirection)
		{
			movementComponent->Direction = movementComponent->NextDirection;
		}
	}

	bool GridMovementSystem::IsValidNextDirection(
		const GEngine::TiledMap2dRendererComponent* mapComponent,
		const GridMovementComponent *movementComponent,
		const GEngine::CardinalDirection direction
		)
	{
		const glm::i32vec2 directionVector = GEngine::CardinalDirectionExtensions::GetDirectionVector(direction);
		const glm::i32vec2 testingPosition = movementComponent->GridPosition + directionVector;

		const bool hasTile = mapComponent->HasTileAtGridPosition(0, testingPosition);

		return hasTile;
	}
}

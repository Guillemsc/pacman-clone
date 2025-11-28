//
// Created by guillem on 11/28/25.
//

#include "MapMovementComponent.h"

#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Extensions/CardinalDirectionExtensions.h"
#include "GEngine/Modules/TimeModule.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapPathfindingManager.h"

namespace PacMan
{
	MapMovementComponent::MapMovementComponent(GEngine::GEngineCoreModules *modules, const std::weak_ptr<GEngine::Entity> &entity)
		: Component(modules, entity)
	{
	}

	void MapMovementComponent::OnTick()
	{
		MoveThroughPath();
	}

	void MapMovementComponent::SetGridPosition(const glm::i32vec2 gridPosition, const GEngine::CellPosition &cellPosition)
	{
		const std::shared_ptr<MapMovementManager> mapMovement = GEngine::ServiceLocator::Get<MapMovementManager>();
		const std::shared_ptr<GEngine::Entity> entity = GetEntity().lock();
		const std::shared_ptr<GEngine::TransformComponent> transform = entity->GetTransform().lock();

		_currentGridPosition = gridPosition;
		_hasValidGridPosition = true;

		const glm::vec2 positionToSet = mapMovement->GridPositionToWorldPosition(gridPosition, cellPosition);

		transform->SetPositionXY(positionToSet);

		TryGenerateNextPathIfEmpty();
	}

	glm::i32vec2 MapMovementComponent::GetGridPosition() const
	{
		return _currentGridPosition;
	}

	void MapMovementComponent::SetNextDirection(const GEngine::CardinalDirection &nextDirection)
	{
		_nextDirectionWhenPathEmpty = nextDirection;
		_hasValidNextDirectionWhenPathEmpty = true;

		const glm::i32vec2 nextDirectionVector = GEngine::CardinalDirectionExtensions::GetDirectionVector(nextDirection);
		const bool isSameMovementDirection = _currentDirectionVector.x == nextDirectionVector.x || _currentDirectionVector.y == nextDirectionVector.y;

		if (!isSameMovementDirection)
		{
			TryGenerateNextPathIfEmpty();
			return;
		}

		const glm::i32vec2 nextPosition = _currentGridPosition + nextDirectionVector;

		const bool nextDirectionWhenPathEmptyIsValid = IsValidNextDirection(_currentGridPosition, _nextDirectionWhenPathEmpty);

		if (nextDirectionWhenPathEmptyIsValid)
		{
			_pathToFollow.clear();
			_pathToFollow.push_back(nextPosition);
			_hasValidLastPathPoint = false;
			_hasValidNextDirectionWhenPathEmpty = false;
		}
	}

	void MapMovementComponent::PathfindToGridPosition(const glm::i32vec2& targetGridPosition)
	{
		if (!_hasValidGridPosition) return;

		const std::shared_ptr<MapPathfindingManager> mapPathfinding = GEngine::ServiceLocator::Get<MapPathfindingManager>();

		_pathToFollow.clear();

		mapPathfinding->GeneratePath(_currentGridPosition, targetGridPosition, _pathToFollow);

		_hasValidLastPathPoint = false;
	}

	void MapMovementComponent::MoveThroughPath()
	{
		if (_pathToFollow.empty()) return;

		const std::shared_ptr<MapMovementManager> mapMovement = GEngine::ServiceLocator::Get<MapMovementManager>();
		const std::shared_ptr<GEngine::Entity> entity = GetEntity().lock();
		const std::shared_ptr<GEngine::TransformComponent> transform = entity->GetTransform().lock();

		glm::i32vec2 nextPathGridPosition = _pathToFollow[0];
		_currentDirectionVector = GEngine::Vec2Extensions::SafeNormalize(nextPathGridPosition - _currentGridPosition);

		const glm::vec2 currentTargetPosition = mapMovement->GridPositionToWorldPosition(nextPathGridPosition);

		const bool hasReachedTarget = MoveTowardsPosition(transform.get(), currentTargetPosition, 50);

		if (hasReachedTarget)
		{
			_lastPathDirectionVector = nextPathGridPosition - _currentGridPosition;
			_currentGridPosition = nextPathGridPosition;
			_hasValidGridPosition = true;
			_hasValidLastPathPoint = true;

			_pathToFollow.erase(_pathToFollow.begin());

			TryGenerateNextPathIfEmpty();
		}
	}

	bool MapMovementComponent::MoveTowardsPosition(
		GEngine::TransformComponent *transform,
		const glm::vec2 targetPosition,
		const float speed
		)
	{
		bool hasReachedTarget = false;

		const float deltaTime = modules->time->GetDeltaTime();

		const glm::vec2 currentPosition = transform->GetPositionXY();

		const glm::vec2 distanceLeft = targetPosition - currentPosition;
		const float distanceLeftMagnitude = glm::length(distanceLeft);
		const glm::vec2 direction = GEngine::Vec2Extensions::SafeNormalize(distanceLeft);

		float distanceToMove = (speed * deltaTime) + _distanceCarriedFromLastPathPoint;
		_distanceCarriedFromLastPathPoint = 0;

		if (distanceToMove >= distanceLeftMagnitude)
		{
			_distanceCarriedFromLastPathPoint = distanceToMove - distanceLeftMagnitude;
			distanceToMove = distanceLeftMagnitude;
			hasReachedTarget = true;
		}

		const glm::vec2 toMove = direction * distanceToMove;
		const glm::vec2 newPosition = currentPosition + toMove;

		transform->SetPositionXY(newPosition);

		return hasReachedTarget;
	}

	void MapMovementComponent::TryGenerateNextPathIfEmpty()
	{
		if(!_pathToFollow.empty()) return;

		const std::shared_ptr<MapMovementManager> mapMovement = GEngine::ServiceLocator::Get<MapMovementManager>();

		if (_hasValidNextDirectionWhenPathEmpty)
		{
			const bool nextDirectionWhenPathEmptyIsValid = IsValidNextDirection(_currentGridPosition, _nextDirectionWhenPathEmpty);

			if (nextDirectionWhenPathEmptyIsValid)
			{
				const glm::i32vec2 directionVector = GEngine::CardinalDirectionExtensions::GetDirectionVector(_nextDirectionWhenPathEmpty);
				const glm::i32vec2 nextPosition = _currentGridPosition + directionVector;

				_pathToFollow.push_back(nextPosition);
				_hasValidLastPathPoint = false;
				_hasValidNextDirectionWhenPathEmpty = false;
				return;
			}
		}

		if (_hasValidLastPathPoint)
		{
			const glm::i32vec2 nextPosition = _currentGridPosition + _lastPathDirectionVector;
			const bool hasTile = mapMovement->IsWalkable(nextPosition);

			if (hasTile)
			{
				_pathToFollow.push_back(nextPosition);
				_hasValidLastPathPoint = false;
				return;
			}
		}
		else
		{
			const std::shared_ptr<MapPathfindingManager> mapPathfinding = GEngine::ServiceLocator::Get<MapPathfindingManager>();
			std::vector<glm::i32vec2> neighbors;
			mapPathfinding->GenerateWalkableNeighbors(_currentGridPosition, neighbors);
			if (!neighbors.empty())
			{
				_pathToFollow.push_back(neighbors[0]);
				_hasValidLastPathPoint = false;
				return;
			}
		}
	}

	bool MapMovementComponent::IsValidNextDirection(const glm::i32vec2& originGridPosition, const GEngine::CardinalDirection direction) const
	{
		const std::shared_ptr<MapMovementManager> mapMovement = GEngine::ServiceLocator::Get<MapMovementManager>();

		const glm::i32vec2 directionVector = GEngine::CardinalDirectionExtensions::GetDirectionVector(direction);
		const glm::i32vec2 testingPosition = originGridPosition + directionVector;

		const bool hasTile = mapMovement->IsWalkable(testingPosition);

		return hasTile;
	}
}

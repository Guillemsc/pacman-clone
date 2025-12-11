//
// Created by guillem on 11/28/25.
//

#include "MapMovementComponent.h"

#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Extensions/CardinalDirectionExtensions.h"
#include "GEngine/Modules/RandomModule.h"
#include "GEngine/Modules/RenderingModule.h"
#include "GEngine/Modules/TimeModule.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapPathfindingManager.h"
#include "spdlog/spdlog.h"

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

	void MapMovementComponent::OnDrawGuizmo()
	{
		if (!_canMove) return;

		const MapMovementManager* mapMovement = GEngine::ServiceLocator::Get<MapMovementManager>();

		glm::vec2 previousWorldPosition = GetEntity().lock()->GetTransform().lock()->GetPositionXY();
		for (glm::i32vec2 gridPosition : _pathToFollow)
		{
			glm::vec2 worldPosition = mapMovement->GridPositionToWorldPosition(gridPosition);

			modules->rendering->Guizmo2dRender()->AddLine(
				previousWorldPosition,
				worldPosition,
				2,
				_guizmoColor
				);

			previousWorldPosition = worldPosition;
		}
	}

	void MapMovementComponent::SetGridPosition(
		const glm::i32vec2& gridPosition,
		const GEngine::CellPosition &cellPosition
		)
	{
		const MapMovementManager* mapMovement = GEngine::ServiceLocator::Get<MapMovementManager>();
		const std::shared_ptr<GEngine::Entity> entity = GetEntity().lock();
		const std::shared_ptr<GEngine::TransformComponent> transform = entity->GetTransform().lock();

		_currentGridPosition = gridPosition;
		_hasValidGridPosition = true;
		_distanceCarriedFromLastPathPoint = 0;
		_hasValidLastPathPointData = false;

		const glm::vec2 positionToSet = mapMovement->GridPositionToWorldPosition(gridPosition, cellPosition);

		transform->SetPositionXY(positionToSet);

		ClearPath();
		TryGenerateNextPathIfEmpty();
	}

	glm::i32vec2 MapMovementComponent::GetGridPosition() const
	{
		return _currentGridPosition;
	}

	void MapMovementComponent::SetCanMove(const bool set)
	{
		_canMove = set;
	}

	void MapMovementComponent::SetCanAutomaticallyFindNextDirection(const bool set)
	{
		_canFindNextDirection = set;
	}

	void MapMovementComponent::SetNextDirection(const GEngine::CardinalDirection &nextDirection)
	{
		const glm::i32vec2 nextDirectionVector = GEngine::CardinalDirectionExtensions::GetDirectionVector(nextDirection);
		const bool isSameMovementDirection = _currentDirectionVector.x == nextDirectionVector.x || _currentDirectionVector.y == nextDirectionVector.y;

		if (isSameMovementDirection)
		{
			const glm::i32vec2 nextPosition = _currentGridPosition + nextDirectionVector;

			const bool nextDirectionWhenPathEmptyIsValid = IsValidNextDirection(_currentGridPosition, nextDirection);

			if (nextDirectionWhenPathEmptyIsValid)
			{
				ClearPath();
				_pathToFollow.push_back(nextPosition);
				return;
			}
		}

		_nextDirectionWhenPathEmpty = nextDirection;
		TryGenerateNextPathIfEmpty();
	}

	PathfindingResult MapMovementComponent::PathfindToGridPosition(const glm::i32vec2& targetGridPosition)
	{
		if (!_hasValidGridPosition) return { false, false, _currentGridPosition };

		MapPathfindingManager* mapPathfinding = GEngine::ServiceLocator::Get<MapPathfindingManager>();

		ClearPath();

		glm::i32vec2 direction = glm::i32vec2(0);

		if (_hasValidLastPathPointData)
		{
			direction = _lastPathPointDirectionVector;
		}

		return mapPathfinding->GeneratePath(
			_currentGridPosition,
			direction,
			targetGridPosition,
			_pathToFollow
			);
	}

	glm::i32vec2 MapMovementComponent::GetDirectionVector() const
	{
		return _currentDirectionVector;
	}

	void MapMovementComponent::SetGuizmoColor(const GEngine::Color01 &color)
	{
		_guizmoColor = color;
	}

	void MapMovementComponent::MoveThroughPath()
	{
		if (!_canMove) return;
		if (_pathToFollow.empty()) return;

		const MapMovementManager* mapMovement = GEngine::ServiceLocator::Get<MapMovementManager>();
		const std::shared_ptr<GEngine::Entity> entity = GetEntity().lock();
		const std::shared_ptr<GEngine::TransformComponent> transform = entity->GetTransform().lock();

		const glm::i32vec2 nextPathGridPosition = _pathToFollow[0];
		_currentDirectionVector = GEngine::Vec2Extensions::SafeNormalize(nextPathGridPosition - _currentGridPosition);

		const glm::vec2 currentTargetPosition = mapMovement->GridPositionToWorldPosition(nextPathGridPosition);

		const bool hasReachedTarget = MoveTowardsPosition(transform.get(), currentTargetPosition, 30);

		if (hasReachedTarget)
		{
			_lastPathPointDirectionVector = nextPathGridPosition - _currentGridPosition;
			_currentGridPosition = nextPathGridPosition;
			_hasValidGridPosition = true;
			_hasValidLastPathPointData = true;

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

		// If we have forced a next direction, we try to follow it
		if (TryGenerateNextPathFromNextDirectionWhenEmpty()) return;

		// Have we selected any previous direction previously? If not, we just select a random one
		if (_hasValidLastPathPointData)
		{
			// Can this entity move autonomously?
			// Entities than can move autonomously never stop, and always keep moving through random directions
			if (_canFindNextDirection)
			{
				// We try to keep moving on our previous direction. If we find an intersection, we pick a random direction.
				if (TryGeneratePathFromRandomValidDirection()) return;

				// In case there is no valid forward random direction, we go backwards from where we came (last resort).
				if (TryGenerateNextPathFromAnyValidNeighbor()) return;
			}
			else
			{
				// We try to keep moving on our previous direction. If we find a wall, we stop.
				if (TryGenerateNextPathFromPreviousDirection()) return;
			}
			return;
		}

		// Pick any walkable direction
		TryGenerateNextPathFromAnyValidNeighbor();
	}

	bool MapMovementComponent::TryGenerateNextPathFromNextDirectionWhenEmpty()
	{
		if (!_nextDirectionWhenPathEmpty.has_value()) return false;

		const GEngine::CardinalDirection nextDirectionWhenPathEmpty = _nextDirectionWhenPathEmpty.value();
		const bool isNextDirectionWhenPathEmptyValid = IsValidNextDirection(_currentGridPosition, nextDirectionWhenPathEmpty);

		if (!isNextDirectionWhenPathEmptyValid) return false;

		const glm::i32vec2 directionVector = GEngine::CardinalDirectionExtensions::GetDirectionVector(nextDirectionWhenPathEmpty);
		const glm::i32vec2 nextPosition = _currentGridPosition + directionVector;

		ClearPath();
		_pathToFollow.push_back(nextPosition);
		_nextDirectionWhenPathEmpty.reset();

		return true;
	}

	bool MapMovementComponent::TryGenerateNextPathFromAnyValidNeighbor()
	{
		MapPathfindingManager* mapPathfinding = GEngine::ServiceLocator::Get<MapPathfindingManager>();

		std::vector<glm::i32vec2> neighbors;
		mapPathfinding->GenerateWalkableNeighbors(_currentGridPosition, {1, 0}, neighbors);

		if (neighbors.empty())return false;

		ClearPath();
		_pathToFollow.push_back(neighbors[0]);

		return true;
	}

	bool MapMovementComponent::TryGenerateNextPathFromPreviousDirection()
	{
		const MapMovementManager* mapMovement = GEngine::ServiceLocator::Get<MapMovementManager>();

		const glm::i32vec2 nextPosition = _currentGridPosition + _lastPathPointDirectionVector;
		const bool hasTile = mapMovement->IsWalkable(nextPosition);

		if (!hasTile)return false;

		ClearPath();
		_pathToFollow.push_back(nextPosition);

		return true;
	}

	bool MapMovementComponent::TryGeneratePathFromRandomValidDirection()
	{
		const std::optional<glm::i32vec2> optionalNextNeighbor = FindNextValidNeighbor();

		if (!optionalNextNeighbor.has_value()) return false;

		ClearPath();
		_pathToFollow.push_back(optionalNextNeighbor.value());

		return true;
	}

	void MapMovementComponent::ClearPath()
	{
		_pathToFollow.clear();
	}

	bool MapMovementComponent::IsValidNextDirection(const glm::i32vec2& originGridPosition, const GEngine::CardinalDirection direction) const
	{
		const MapMovementManager* mapMovement = GEngine::ServiceLocator::Get<MapMovementManager>();

		const glm::i32vec2 directionVector = GEngine::CardinalDirectionExtensions::GetDirectionVector(direction);
		const glm::i32vec2 testingPosition = originGridPosition + directionVector;

		const bool hasTile = mapMovement->IsWalkable(testingPosition);

		return hasTile;
	}

	std::optional<glm::i32vec2> MapMovementComponent::FindNextValidNeighbor() const
	{
		MapPathfindingManager* mapPathfinding = GEngine::ServiceLocator::Get<MapPathfindingManager>();

		std::vector<glm::i32vec2> neighbors;
		mapPathfinding->GenerateWalkableNeighbors(_currentGridPosition, _lastPathPointDirectionVector, neighbors);

		if (neighbors.empty()) return std::nullopt;

		const int randomIndex = GEngine::RandomModule::Range(0, neighbors.size());
		return neighbors[randomIndex];
	}
}

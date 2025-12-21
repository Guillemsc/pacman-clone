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
	MapMovementComponent::MapMovementComponent(
		GEngine::GEngineCoreModules *modules,
		const std::weak_ptr<GEngine::Entity> &entity,
		MapMovementManager* mapMovementManager,
		MapPathfindingManager* mapPathfindingManager
		)
		: Component(modules, entity),
		_mapMovementManager(mapMovementManager),
		_mapPathfindingManager(mapPathfindingManager)
	{
	}

	void MapMovementComponent::OnTick()
	{
		MoveThroughPath();
	}

	void MapMovementComponent::OnDrawGuizmo()
	{
		if (!_canMove) return;

		glm::vec2 previousWorldPosition = GetEntity().lock()->GetTransform().lock()->GetPositionXY();

		for (const PathPointData& pathPoint : _pathToFollow)
		{
			glm::vec2 worldPosition = _mapMovementManager->GridPositionToWorldPosition(pathPoint.gridPosition);

			modules->rendering->Guizmo2dRender()->AddLine(
				previousWorldPosition,
				worldPosition,
				2,
				_guizmoColor
				);

			previousWorldPosition = worldPosition;
		}
	}

	MapMovementManager* MapMovementComponent::GetMapMovementManager() const
	{
		return _mapMovementManager;
	}

	void MapMovementComponent::SetGridPosition(
		const glm::i32vec2& gridPosition,
		const GEngine::CellPosition &cellPosition
		)
	{
		const std::shared_ptr<GEngine::Entity> entity = GetEntity().lock();
		const std::shared_ptr<GEngine::TransformComponent> transform = entity->GetTransform().lock();

		_currentGridPosition = gridPosition;
		_hasValidGridPosition = true;
		_distanceCarriedFromLastPathPoint = 0;
		_hasValidLastPathPointData = false;

		const glm::vec2 positionToSet = _mapMovementManager->GridPositionToWorldPosition(gridPosition, cellPosition);

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
		_canAutomaticallyFindNextDirection = set;
	}

	void MapMovementComponent::SetCanAutomaticallyKeepMovingOnCurrentDirection(const bool set)
	{
		_canAutomaticallyKeepMovingOnCurrentDirection = set;
	}

	void MapMovementComponent::SetNextDirection(const GEngine::CardinalDirection &nextDirection)
	{
		const glm::i32vec2 nextDirectionVector = GEngine::CardinalDirectionExtensions::GetDirectionVector(nextDirection);
		const bool isSameMovementDirection = _gridDirectionVector.x == nextDirectionVector.x || _gridDirectionVector.y == nextDirectionVector.y;

		if (isSameMovementDirection)
		{
			const glm::i32vec2 nextPosition = _currentGridPosition + nextDirectionVector;

			const bool nextDirectionWhenPathEmptyIsValid = IsValidNextDirection(_currentGridPosition, nextDirection);

			if (nextDirectionWhenPathEmptyIsValid)
			{
				ClearPath();
				_pathToFollow.push_back({ nextPosition, false });
				return;
			}
		}

		_nextDirectionWhenPathEmpty = nextDirection;
		TryGenerateNextPathIfEmpty();
	}

	void MapMovementComponent::SwitchPathfindingDirection()
	{
		if (_pathToFollow.size() == 0) return;

		const PathPointData targetPathPoint = _pathToFollow[_pathToFollow.size() - 1];
		if (targetPathPoint.fromPortal) return;

		_gridDirectionVector = -_gridDirectionVector;
		_targetGridPosition = _currentGridPosition;

		ClearPath();
		PathfindToGridPosition(targetPathPoint.gridPosition);
	}

	PathfindingResult MapMovementComponent::PathfindToGridPosition(const glm::i32vec2& targetGridPosition)
	{
		if (!_hasValidGridPosition) return { false, false, _currentGridPosition };

		glm::i32vec2 direction = glm::i32vec2(0);

		glm::vec2 startGridPosition = _currentGridPosition;

		if (_hasValidLastPathPointData)
		{
			direction = _gridDirectionVector;
			startGridPosition = _targetGridPosition;
		}

		std::vector<PathPointData> newGeneratedPath;

		const PathfindingResult pathfindingResult = _mapPathfindingManager->GeneratePath(
			startGridPosition,
			direction,
			targetGridPosition,
			newGeneratedPath
			);

		if (pathfindingResult.couldReachAnyPosition)
		{
			ClearPath();
			_pathToFollow = newGeneratedPath;
			_isMovingRandomly = false;
		}

		return pathfindingResult;
	}

	void MapMovementComponent::SetMovementSpeed(const float speed)
	{
		_movementSpeed = speed;
	}

	glm::i32vec2 MapMovementComponent::GetGridDirectionVector() const
	{
		return _gridDirectionVector;
	}

	bool MapMovementComponent::GetIsMovingRandomly() const
	{
		return _isMovingRandomly;
	}

	float MapMovementComponent::GetDistanceMovedThisFrame() const
	{
		return _distanceMovedThisFrame;
	}

	void MapMovementComponent::SetGuizmoColor(const GEngine::Color01 &color)
	{
		_guizmoColor = color;
	}

	void MapMovementComponent::MoveThroughPath()
	{
		_distanceMovedThisFrame = 0.0f;

		if (!_canMove) return;
		if (_pathToFollow.empty()) return;

		const std::shared_ptr<GEngine::Entity> entity = GetEntity().lock();
		const std::shared_ptr<GEngine::TransformComponent> transform = entity->GetTransform().lock();

		const PathPointData pathPoint = _pathToFollow[0];

		if (pathPoint.fromPortal)
		{
			const glm::vec2 currentTargetPosition = _mapMovementManager->GridPositionToWorldPosition(pathPoint.gridPosition);
			transform->SetPositionXY(currentTargetPosition);
			_currentGridPosition = pathPoint.gridPosition;

			const std::optional<MapPortalData> portalData = _mapMovementManager->GetPortal(pathPoint.gridPosition);
			_gridDirectionVector = portalData.value().exitDirection;

			_pathToFollow.erase(_pathToFollow.begin());

			TryGenerateNextPathIfEmpty();
		}
		else
		{
			_targetGridPosition = pathPoint.gridPosition;

			if (_targetGridPosition != _currentGridPosition)
			{
				_gridDirectionVector = GEngine::Vec2Extensions::Normalize(_targetGridPosition - _currentGridPosition);
			}

			const glm::vec2 currentTargetPosition = _mapMovementManager->GridPositionToWorldPosition(_targetGridPosition);

			const bool hasReachedTarget = MoveTowardsPosition(transform.get(), currentTargetPosition, _movementSpeed);

			if (hasReachedTarget)
			{
				_hasValidLastPathPointData = true;
				_currentGridPosition = _targetGridPosition;
				_hasValidGridPosition = true;

				_pathToFollow.erase(_pathToFollow.begin());

				TryGenerateNextPathIfEmpty();
			}
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

		_distanceMovedThisFrame = speed + _distanceCarriedFromLastPathPoint;
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

		_isMovingRandomly = false;

		// If we have forced a next direction, we try to follow it
		if (TryGenerateNextPathFromNextDirectionWhenEmpty()) return;

		// Have we selected any previous direction previously? If not, we just select a random one
		if (_hasValidLastPathPointData)
		{
			// Can this entity move autonomously?
			// Entities than can move autonomously never stop, and always keep moving through random directions
			if (_canAutomaticallyFindNextDirection)
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
		_pathToFollow.push_back({ nextPosition, false });
		_nextDirectionWhenPathEmpty.reset();

		return true;
	}

	bool MapMovementComponent::TryGenerateNextPathFromAnyValidNeighbor()
	{
		std::vector<PathPointData> neighbors;
		_mapPathfindingManager->GenerateWalkableNeighbors(_currentGridPosition, {1, 0}, neighbors);

		if (neighbors.empty()) return false;

		ClearPath();
		_pathToFollow.push_back(neighbors[0]);

		_isMovingRandomly = true;

		return true;
	}

	bool MapMovementComponent::TryGenerateNextPathFromPreviousDirection()
	{
		if (!_canAutomaticallyKeepMovingOnCurrentDirection) return false;

		const auto optionalPortal = _mapMovementManager->GetPortal(_currentGridPosition);

		if (optionalPortal.has_value())
		{
			const MapPortalData portalData = optionalPortal.value();

			if (portalData.enterDirection == _gridDirectionVector)
			{
				const MapPortalData connectedPortalData = _mapMovementManager->GetPortal(portalData.connectedPortalId).value();
				ClearPath();
				_pathToFollow.push_back({ connectedPortalData.gridPosition, true });
				return true;
			}
		}

		const glm::i32vec2 nextPosition = _currentGridPosition + _gridDirectionVector;
		const bool hasTile = _mapMovementManager->IsWalkable(nextPosition);

		if (!hasTile) return false;

		ClearPath();
		_pathToFollow.push_back({ nextPosition, false });

		return true;
	}

	bool MapMovementComponent::TryGeneratePathFromRandomValidDirection()
	{
		const std::optional<PathPointData> optionalNextNeighbor = FindNextValidNeighbor();

		if (!optionalNextNeighbor.has_value()) return false;

		ClearPath();
		_pathToFollow.push_back(optionalNextNeighbor.value());

		_isMovingRandomly = true;

		return true;
	}

	void MapMovementComponent::ClearPath()
	{
		_pathToFollow.clear();
	}

	bool MapMovementComponent::IsValidNextDirection(const glm::i32vec2& originGridPosition, const GEngine::CardinalDirection direction) const
	{
		const glm::i32vec2 directionVector = GEngine::CardinalDirectionExtensions::GetDirectionVector(direction);
		const glm::i32vec2 testingPosition = originGridPosition + directionVector;

		const bool hasTile = _mapMovementManager->IsWalkable(testingPosition);

		return hasTile;
	}

	std::optional<PathPointData> MapMovementComponent::FindNextValidNeighbor() const
	{
		std::vector<PathPointData> neighbors;
		_mapPathfindingManager->GenerateWalkableNeighbors(_currentGridPosition, _gridDirectionVector, neighbors);

		if (neighbors.empty()) return std::nullopt;

		const int randomIndex = GEngine::RandomModule::Range(0, neighbors.size());
		return neighbors[randomIndex];
	}
}

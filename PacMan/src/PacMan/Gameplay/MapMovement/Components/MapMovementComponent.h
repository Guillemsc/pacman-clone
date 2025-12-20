//
// Created by guillem on 11/28/25.
//

#ifndef MAPMOVEMENTCOMPONENT_H
#define MAPMOVEMENTCOMPONENT_H

#include <optional>

#include "GEngine/Colors/Color01.h"
#include "GEngine/Components/Component.h"
#include "GEngine/Data/CellPosition.h"
#include "GEngine/Directions/CardinalDirection.h"
#include "GEngine/Extensions/Vec2Extensions.h"
#include "glm/fwd.hpp"
#include "PacMan/Gameplay/MapMovement/Data/PathfindingResult.h"
#include "PacMan/Gameplay/MapMovement/Data/PathPointData.h"

namespace PacMan
{
	class MapMovementManager;
	class MapPathfindingManager;

	class MapMovementComponent final : public GEngine::Component
	{
		REGISTER_COMPONENT(MapMovementComponent)

	public:
		explicit MapMovementComponent(
			GEngine::GEngineCoreModules* modules,
			const std::weak_ptr<GEngine::Entity> &entity,
			MapMovementManager* mapMovementManager,
			MapPathfindingManager* mapPathfindingManager
			);

		void OnTick() override;
		void OnDrawGuizmo() override;

		void SetGridPosition(
			const glm::i32vec2& gridPosition,
			const GEngine::CellPosition& cellPosition = GEngine::CellPosition::CENTER
			);
		[[nodiscard]] glm::i32vec2 GetGridPosition() const;

		void SetCanMove(bool set);
		void SetCanAutomaticallyFindNextDirection(bool set);
		void SetCanAutomaticallyKeepMovingOnCurrentDirection(bool set);

		void SetNextDirection(const GEngine::CardinalDirection& nextDirection);
		PathfindingResult PathfindToGridPosition(const glm::i32vec2& targetGridPosition);

		void SetMovementSpeed(float speed);

		[[nodiscard]] glm::i32vec2 GetGridDirectionVector() const;
		[[nodiscard]] bool GetIsMovingRandomly() const;

		[[nodiscard]] float GetDistanceMovedThisFrame() const;

		void SetGuizmoColor(const GEngine::Color01& color);

	private:
		void MoveThroughPath();
		bool MoveTowardsPosition(GEngine::TransformComponent* transform, glm::vec2 targetPosition, float speed);

		void TryGenerateNextPathIfEmpty();
		bool TryGenerateNextPathFromNextDirectionWhenEmpty();
		bool TryGenerateNextPathFromPreviousDirection();
		bool TryGenerateNextPathFromAnyValidNeighbor();
		bool TryGeneratePathFromRandomValidDirection();

		void ClearPath();

		bool IsValidNextDirection(
			const glm::i32vec2& originGridPosition,
			GEngine::CardinalDirection direction
			) const;

		std::optional<PathPointData> FindNextValidNeighbor() const;

	private:
		MapMovementManager* const _mapMovementManager;
		MapPathfindingManager* const _mapPathfindingManager;

		bool _canMove = true;
		bool _canAutomaticallyFindNextDirection = false;
		bool _canAutomaticallyKeepMovingOnCurrentDirection = true;

		float _movementSpeed = 30.0f;

		glm::i32vec2 _currentGridPosition = glm::i32vec2(0);
		bool _hasValidGridPosition = false;

		float _distanceMovedThisFrame = 0.0f;

		std::vector<PathPointData> _pathToFollow;
		float _distanceCarriedFromLastPathPoint = 0;
		glm::i32vec2 _currentDirectionVector = glm::i32vec2(0);
		glm::i32vec2 _gridDirectionVector = glm::i32vec2(0);
		glm::i32vec2 _targetGridPosition = glm::i32vec2(0);
		bool _hasValidLastPathPointData = false;

		std::optional<GEngine::CardinalDirection> _nextDirectionWhenPathEmpty;

		bool _isMovingRandomly = false;

		GEngine::Color01 _guizmoColor = {0, 1, 0, 1};
	};
}

#endif //MAPMOVEMENTCOMPONENT_H

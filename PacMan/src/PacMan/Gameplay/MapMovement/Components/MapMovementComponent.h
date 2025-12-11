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
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"

namespace PacMan
{
	class MapMovementComponent final : public GEngine::Component
	{
		REGISTER_COMPONENT(MapMovementComponent)

	public:
		explicit MapMovementComponent(GEngine::GEngineCoreModules* modules, const std::weak_ptr<GEngine::Entity> &entity);

		void OnTick() override;
		void OnDrawGuizmo() override;

		void SetGridPosition(
			const glm::i32vec2& gridPosition,
			const GEngine::CellPosition& cellPosition = GEngine::CellPosition::CENTER
			);
		[[nodiscard]] glm::i32vec2 GetGridPosition() const;

		void SetCanMove(bool set);
		void SetCanAutomaticallyFindNextDirection(bool set);
		void SetNextDirection(const GEngine::CardinalDirection& nextDirection);
		PathfindingResult PathfindToGridPosition(const glm::i32vec2& targetGridPosition);

		[[nodiscard]] glm::i32vec2 GetDirectionVector() const;

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

		std::optional<glm::i32vec2> FindNextValidNeighbor() const;

	private:
		bool _canMove = true;
		bool _canFindNextDirection = false;

		glm::i32vec2 _currentGridPosition = glm::i32vec2(0);
		bool _hasValidGridPosition = false;

		std::vector<glm::i32vec2> _pathToFollow;
		float _distanceCarriedFromLastPathPoint = 0;
		glm::i32vec2 _currentDirectionVector = glm::i32vec2(0);
		glm::i32vec2 _lastPathPointDirectionVector = glm::i32vec2(0);
		bool _hasValidLastPathPointData = false;

		std::optional<GEngine::CardinalDirection> _nextDirectionWhenPathEmpty;

		GEngine::Color01 _guizmoColor = {0, 1, 0, 1};
	};
}

#endif //MAPMOVEMENTCOMPONENT_H

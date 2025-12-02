//
// Created by guillem on 11/28/25.
//

#ifndef MAPMOVEMENTCOMPONENT_H
#define MAPMOVEMENTCOMPONENT_H

#include <optional>

#include "GEngine/Components/Component.h"
#include "GEngine/Data/CellPosition.h"
#include "GEngine/Directions/CardinalDirection.h"
#include "GEngine/Extensions/Vec2Extensions.h"
#include "glm/fwd.hpp"

namespace PacMan
{
	class MapMovementComponent final : public GEngine::Component
	{
		DECLARE_COMPONENT(MapMovementComponent)

	public:
		explicit MapMovementComponent(GEngine::GEngineCoreModules* modules, const std::weak_ptr<GEngine::Entity> &entity);

		void OnTick() override;

		void SetGridPosition(
			const glm::i32vec2& gridPosition,
			const GEngine::CellPosition& cellPosition = GEngine::CellPosition::CENTER
			);
		glm::i32vec2 GetGridPosition() const;

		void SetCanMove(bool set);

		void SetNextDirection(const GEngine::CardinalDirection& nextDirection);

		void PathfindToGridPosition(const glm::i32vec2& targetGridPosition);

	private:
		void MoveThroughPath();
		bool MoveTowardsPosition(GEngine::TransformComponent* transform, glm::vec2 targetPosition, float speed);

		void TryGenerateNextPathIfEmpty();
		void ClearPath();

		bool IsValidNextDirection(
			const glm::i32vec2& originGridPosition,
			GEngine::CardinalDirection direction
			) const;

	private:
		glm::i32vec2 _currentGridPosition = glm::i32vec2(0);
		bool _hasValidGridPosition = false;

		bool _canMove = true;

		std::vector<glm::i32vec2> _pathToFollow;
		float _distanceCarriedFromLastPathPoint = 0;
		glm::i32vec2 _currentDirectionVector = glm::i32vec2(0);
		glm::i32vec2 _lastPathPointDirectionVector = glm::i32vec2(0);
		bool _hasValidLastPathPointData = false;

		std::optional<GEngine::CardinalDirection> _nextDirectionWhenPathEmpty;
	};
}

#endif //MAPMOVEMENTCOMPONENT_H

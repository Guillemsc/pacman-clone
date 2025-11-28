//
// Created by guillem on 11/27/25.
//

#ifndef MAPPATHFINDINGSYSTEM_H
#define MAPPATHFINDINGSYSTEM_H

#include <memory>
#include <vector>

#include "GEngine/Directions/CardinalDirection.h"
#include "GEngine/Systems/System.h"
#include "glm/fwd.hpp"

namespace PacMan
{
	class MapMovementManager;
}

namespace PacMan
{
	class MapPathfindingComponent;
}

namespace PacMan
{
	class MapPathfindingManager;

	class MapPathfindingSystem final : public GEngine::System
	{
	public:
		explicit MapPathfindingSystem(
			MapPathfindingManager* mapPathfindingManager,
			MapMovementManager* mapMovementManager
			);

		void Tick() override;

		void Add(const std::weak_ptr<MapPathfindingComponent> &component);

	private:
		void TickComponent(const std::shared_ptr<MapPathfindingComponent>& component);

		static GEngine::CardinalDirection GetDirectionFromOriginAndTargetGridPositions(
			const glm::i32vec2& origin,
			const glm::i32vec2& target
		);

	private:
		MapPathfindingManager* const _mapPathfindingManager;
		MapMovementManager* const _mapMovementManager;

		std::vector<std::weak_ptr<MapPathfindingComponent>> _components;
	};
}

#endif //MAPPATHFINDINGSYSTEM_H

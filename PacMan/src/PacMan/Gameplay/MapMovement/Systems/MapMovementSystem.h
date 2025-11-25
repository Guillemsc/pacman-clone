//
// Created by guillem on 6/28/25.
//

#ifndef MAPMOVEMENTSYSTEM_H
#define MAPMOVEMENTSYSTEM_H

#include <memory>
#include <vector>

#include "GEngine/Directions/CardinalDirection.h"
#include "GEngine/Systems/System.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"

namespace GEngine
{
	class TiledMap2dRendererComponent;
}

namespace PacMan
{
	class MapMovementComponent;

	class MapMovementSystem : public GEngine::System
	{
	public:
		explicit MapMovementSystem(const std::weak_ptr<MapMovementManager> &mapMovementManager);

		void Tick() override;

		void Add(const std::weak_ptr<MapMovementComponent> &component);

	private:
		static bool TryApplyNextDirection(
			const MapMovementManager* mapMovementManager,
			MapMovementComponent *movementComponent,
			const GEngine::CardinalDirection direction
		);

		static bool IsValidNextDirection(
			const MapMovementManager* mapMovementManager,
			const MapMovementComponent* movementComponent,
			GEngine::CardinalDirection direction
			);

	private:
		std::weak_ptr<MapMovementManager> _mapMovementManagerPtr;
		std::vector<std::weak_ptr<MapMovementComponent>> _components;
	};
}

#endif //MAPMOVEMENTSYSTEM_H

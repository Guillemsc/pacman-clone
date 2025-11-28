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
	class OldMapMovementComponent;

	class MapMovementSystem final : public GEngine::System
	{
	public:
		explicit MapMovementSystem(MapMovementManager* mapMovementManager);

		void Tick() override;

		void Add(const std::weak_ptr<OldMapMovementComponent> &component);

	private:
		void TickComponent(const std::shared_ptr<OldMapMovementComponent>& component);

		static bool TryApplyNextDirection(
			const MapMovementManager* mapMovementManager,
			OldMapMovementComponent *movementComponent,
			GEngine::CardinalDirection direction
		);

		static bool IsValidNextDirection(
			const MapMovementManager* mapMovementManager,
			const OldMapMovementComponent* movementComponent,
			GEngine::CardinalDirection direction
			);

	private:
		MapMovementManager* const _mapMovementManager;
		std::vector<std::weak_ptr<OldMapMovementComponent>> _components;
	};
}

#endif //MAPMOVEMENTSYSTEM_H

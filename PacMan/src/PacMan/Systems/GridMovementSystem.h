//
// Created by guillem on 6/28/25.
//

#ifndef MAPMOVEMENTSYSTEM_H
#define MAPMOVEMENTSYSTEM_H

#include <memory>
#include <vector>

#include "GEngine/Directions/CardinalDirection.h"
#include "GEngine/Systems/System.h"

namespace GEngine
{
	class TiledMap2dRendererComponent;
}

namespace PacMan
{
	class GridMovementComponent;

	class GridMovementSystem : public GEngine::System
	{
	public:
		GridMovementSystem(const std::weak_ptr<GEngine::TiledMap2dRendererComponent> &tileMapComponent);

		void Tick() override;

		void Add(const std::weak_ptr<GridMovementComponent> &component);

	private:
		static void TryApplyNextDirection(
			const GEngine::TiledMap2dRendererComponent* mapComponent,
			GridMovementComponent *movementComponent,
			const GEngine::CardinalDirection direction
		);

		static bool IsValidNextDirection(
			const GEngine::TiledMap2dRendererComponent* mapComponent,
			const GridMovementComponent* movementComponent,
			GEngine::CardinalDirection direction
			);

	private:
		std::weak_ptr<GEngine::TiledMap2dRendererComponent> _tileMapComponentPtr;
		std::vector<std::weak_ptr<GridMovementComponent>> _components;
	};
}

#endif //MAPMOVEMENTSYSTEM_H

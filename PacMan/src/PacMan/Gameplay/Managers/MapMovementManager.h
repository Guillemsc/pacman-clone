//
// Created by guillem on 7/28/25.
//

#ifndef MAPMOVEMENTMANAGER_H
#define MAPMOVEMENTMANAGER_H

#include <memory>

#include "glm/vec2.hpp"

namespace GEngine
{
	class TiledMap2dRendererComponent;
}

namespace PacMan
{
	class GridMovementComponent;

	class MapMovementManager
	{
	public:
		MapMovementManager(
			const std::weak_ptr<GEngine::TiledMap2dRendererComponent>& tiledMap,
			std::int32_t walkabilityLayerIndex
			);

		void SetGridPosition(const std::weak_ptr<GridMovementComponent> &gridMovementComponentPtr, const glm::ivec2& gridPosition) const;
		glm::vec2 GridPositionToWorldPosition(const glm::ivec2& gridPosition) const;
		bool IsWalkable(const glm::ivec2& gridPosition) const;

	private:
		std::weak_ptr<GEngine::TiledMap2dRendererComponent> _tiledMap;
		std::int32_t _walkabilityLayerIndex = 0;
	};
}

#endif //MAPMOVEMENTMANAGER_H

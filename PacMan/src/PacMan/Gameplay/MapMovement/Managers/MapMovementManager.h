//
// Created by guillem on 7/28/25.
//

#ifndef MAPMOVEMENTMANAGER_H
#define MAPMOVEMENTMANAGER_H

#include <memory>

#include "GEngine/Data/CellPosition.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	class TiledMap2dRendererComponent;
}

namespace PacMan
{
	class OldMapMovementComponent;

	class MapMovementManager
	{
	public:
		void Setup(const std::weak_ptr<GEngine::TiledMap2dRendererComponent>& tiledMap);

		glm::vec2 GridPositionToWorldPosition(const glm::ivec2& gridPosition, GEngine::CellPosition cellPosition = GEngine::CellPosition::CENTER) const;
		bool IsWalkable(const glm::ivec2& gridPosition) const;

	private:
		std::weak_ptr<GEngine::TiledMap2dRendererComponent> _tiledMap;
		std::int32_t _walkabilityLayerIndex = 0;
	};
}

#endif //MAPMOVEMENTMANAGER_H

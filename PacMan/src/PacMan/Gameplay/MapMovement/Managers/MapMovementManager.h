//
// Created by guillem on 7/28/25.
//

#ifndef MAPMOVEMENTMANAGER_H
#define MAPMOVEMENTMANAGER_H

#include <memory>
#include <optional>
#include <vector>

#include "GEngine/Data/CellPosition.h"
#include "glm/vec2.hpp"
#include "PacMan/Gameplay/MapLoading/Data/MapPortalData.h"

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
		void Setup(
			const std::weak_ptr<GEngine::TiledMap2dRendererComponent>& tiledMap,
			const std::vector<MapPortalData>& portals
			);

		glm::vec2 GridPositionToWorldPosition(const glm::ivec2& gridPosition, GEngine::CellPosition cellPosition = GEngine::CellPosition::CENTER) const;
		bool IsWalkable(const glm::ivec2& gridPosition) const;
		std::optional<MapPortalData> GetPortal(const glm::ivec2& gridPosition) const;
		std::optional<MapPortalData> GetPortal(const std::int32_t portalIndex) const;

	private:
		std::weak_ptr<GEngine::TiledMap2dRendererComponent> _tiledMap;
		std::int32_t _walkabilityLayerIndex = 0;
		std::vector<MapPortalData> _portals;
	};
}

#endif //MAPMOVEMENTMANAGER_H

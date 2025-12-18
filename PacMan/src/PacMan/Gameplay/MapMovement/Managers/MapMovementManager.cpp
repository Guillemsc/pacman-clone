//
// Created by guillem on 7/28/25.
//

#include "MapMovementManager.h"

#include "GEngine/Components/TiledMap2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Extensions/VectorExtensions.h"

namespace PacMan
{
	void MapMovementManager::Setup(
		const std::weak_ptr<GEngine::TiledMap2dRendererComponent> &tiledMap,
		const std::vector<MapPortalData>& portals
		)
	{
		_tiledMap = tiledMap;
		_portals = portals;

		const std::shared_ptr<GEngine::TiledMap2dRendererComponent> lTiledMap = _tiledMap.lock();

		if (lTiledMap)
		{
			_walkabilityLayerIndex = lTiledMap->GetTileLayerIndexFromName("Walkability");
		}
	}

	glm::vec2 MapMovementManager::GridPositionToWorldPosition(const glm::ivec2 &gridPosition, const GEngine::CellPosition cellPosition) const
	{
		const std::shared_ptr<GEngine::TiledMap2dRendererComponent> tiledMapComponent = _tiledMap.lock();
		if (!tiledMapComponent) return glm::vec2(0);

		return tiledMapComponent->GridPositionToWorldPosition(
			gridPosition,
			cellPosition
			);
	}

	bool MapMovementManager::IsWalkable(const glm::ivec2 &gridPosition) const
	{
		const std::shared_ptr<GEngine::TiledMap2dRendererComponent> tiledMapComponent = _tiledMap.lock();
		if (!tiledMapComponent) return false;

		return tiledMapComponent->HasTileAtGridPosition(
			_walkabilityLayerIndex,
			gridPosition
			);
	}

	std::optional<MapPortalData> MapMovementManager::GetPortal(const glm::ivec2 &gridPosition) const
	{
		// Not very fast, but we only have a max of 4 portals, so...
		for (const MapPortalData& portal : _portals)
		{
			if (portal.gridPosition == gridPosition) return portal;
		}

		return std::nullopt;
	}

	std::optional<MapPortalData> MapMovementManager::GetPortal(const std::int32_t portalIndex) const
	{
		if (GEngine::VectorExtensions::IsIndexOutsideBounds(_portals, portalIndex)) return std::nullopt;

		return _portals[portalIndex];
	}
}

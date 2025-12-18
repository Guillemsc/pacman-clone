//
// Created by guillem on 7/28/25.
//

#include "MapMovementManager.h"

#include "GEngine/Components/TiledMap2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"

namespace PacMan
{
	void MapMovementManager::Setup(const std::weak_ptr<GEngine::TiledMap2dRendererComponent> &tiledMap)
	{
		_tiledMap = tiledMap;

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
}

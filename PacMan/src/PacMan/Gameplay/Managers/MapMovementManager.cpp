//
// Created by guillem on 7/28/25.
//

#include "MapMovementManager.h"

#include "GEngine/Components/TiledMap2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "PacMan/Gameplay/Components/GridMovementComponent.h"

namespace PacMan
{
	MapMovementManager::MapMovementManager(
		const std::weak_ptr<GEngine::TiledMap2dRendererComponent> &tiledMap,
		const std::int32_t walkabilityLayerIndex
		)
	{
		_tiledMap = tiledMap;
		_walkabilityLayerIndex = walkabilityLayerIndex;
	}

	void MapMovementManager::SetGridPosition(
		const std::weak_ptr<GridMovementComponent> &gridMovementComponentPtr,
		const glm::ivec2 &gridPosition
		) const
	{
		const std::shared_ptr<GridMovementComponent> gridMovementComponent = gridMovementComponentPtr.lock();
		if (!gridMovementComponent) return;

		const std::shared_ptr<GEngine::Entity> entity = gridMovementComponent->GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<GEngine::TransformComponent> transform = entity->GetTransform().lock();
		if (!transform) return;

		const std::shared_ptr<GEngine::TiledMap2dRendererComponent> tiledMapComponent = _tiledMap.lock();
		if (!tiledMapComponent) return;

		const bool hasTile = tiledMapComponent->HasTileAtGridPosition(_walkabilityLayerIndex, gridPosition);
		if (!hasTile) return;

		const glm::vec2 worldPosition = tiledMapComponent->GridPositionToWorldPosition(
			gridPosition,
			GEngine::CENTER
			);

		gridMovementComponent->GridPosition = gridPosition;
		transform->SetPositionXY(worldPosition);
	}

	glm::vec2 MapMovementManager::GridPositionToWorldPosition(const glm::ivec2 &gridPosition) const
	{
		const std::shared_ptr<GEngine::TiledMap2dRendererComponent> tiledMapComponent = _tiledMap.lock();
		if (!tiledMapComponent) return glm::vec2(0);

		return tiledMapComponent->GridPositionToWorldPosition(
			gridPosition,
			GEngine::CENTER
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

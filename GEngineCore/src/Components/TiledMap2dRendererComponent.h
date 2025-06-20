//
// Created by guillem on 6/20/25.
//

#ifndef TILEDMAP2DRENDERERCOMPONENT_H
#define TILEDMAP2DRENDERERCOMPONENT_H

#include "Component.h"
#include "glm/vec2.hpp"

namespace tmx
{
	class Map;
	class TileLayer;
}

namespace GEngineCore
{
	class TiledMapResource;

	class TiledMap2dRendererComponent final : public Component
	{
	public:
		explicit TiledMap2dRendererComponent(const std::weak_ptr<Entity> &entity);

		static ComponentType GetTypeStatic() { return ComponentType::TILED_MAP_2D_RENDERER; }
		ComponentType GetType() override { return GetTypeStatic(); }
		const char* GetTypeName() override { return "TiledMap2dRenderer"; }

		void OnTick() override;

		void SetTiledMap(const std::weak_ptr<TiledMapResource> &resource);

		glm::i32vec2 GetLayerGridSize(std::int32_t layerIndex) const;
		bool HasTileAtGridPosition(std::int32_t x, std::int32_t y) const;
		glm::vec2 GridPositionToWorldPosition(std::int32_t layerIndex, std::int32_t x, std::int32_t y) const;

	private:
		static glm::vec2 GridPositionToWorldPosition(
			const tmx::TileLayer& tileLayer,
			glm::vec2 tilemapPosition,
			float tilemapRotation,
			glm::vec2 tilemapScale,
			const tmx::Map* mapData,
			std::int32_t x,
			std::int32_t y
			);

	private:
		std::weak_ptr<TiledMapResource> _tiledMapPtr;
	};
}

#endif //TILEDMAP2DRENDERERCOMPONENT_H

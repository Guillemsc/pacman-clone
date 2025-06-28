//
// Created by guillem on 6/20/25.
//

#ifndef TILEDMAP2DRENDERERCOMPONENT_H
#define TILEDMAP2DRENDERERCOMPONENT_H

#include "Component.h"
#include "GEngine/Data/TiledLayerData.h"
#include "raylib.h"
#include "GEngine/Data/CellPosition.h"
#include "glm/vec2.hpp"
#include "tmxlite/TileLayer.hpp"
#include "tmxlite/Types.hpp"

namespace tmx
{
	class Tileset;
	class Map;
	class TileLayer;
}

namespace GEngine
{
	class TiledMapResource;

	class TiledMap2dRendererComponent final : public Component
	{
	public:
		explicit TiledMap2dRendererComponent(const std::weak_ptr<Entity> &entity);

		const char* GetTypeName() override { return "TiledMap2dRenderer"; }

		void OnTick() override;

		void SetTiledMap(const std::weak_ptr<TiledMapResource> &resource);
		std::weak_ptr<TiledMapResource> GetTiledMap() const;

		int GetLayersCount() const;
		glm::i32vec2 GetLayerGridSize(std::int32_t layerIndex) const;
		bool HasTileAtGridPosition(std::int32_t x, std::int32_t y) const;

		glm::vec2 GridPositionToWorldPosition(std::int32_t layerIndex, const glm::i32vec2& gridPosition, CellPosition cellPosition = CellPosition::BOTTOM_LEFT) const;
		glm::i32vec2 WorldPositionToGridPosition(std::int32_t layerIndex, const glm::vec2& worldPosition) const;

		void SetLayerVisible(std::int32_t layerIndex, bool visible);
		bool GetIsLayerVisible(std::int32_t layerIndex) const;

	private:
		void GenerateLayersData();

		static glm::vec2 GridPositionToWorldPosition(
			const tmx::TileLayer& tileLayer,
			glm::vec2 tilemapPosition,
			float tilemapRotation,
			glm::vec2 tilemapScale,
			const tmx::Map* mapData,
			std::int32_t x,
			std::int32_t y,
			CellPosition cellPosition = CellPosition::BOTTOM_LEFT
			);

		static void RenderLayerGrid(
			const ResourcesModule* resourcesModule,
			const TiledMapResource* tiledMapResource,
			const tmx::Map* mapData,
			const std::vector<tmx::TileLayer::Tile>& layerTileIds,
			const tmx::Vector2u pixelSizeOfTile,
			const tmx::TileLayer& tileLayer,
			const tmx::Vector2u& layerGridSize,
			const glm::vec2& position,
			const float rotation,
			const glm::vec2& scale
			);

	private:
		std::weak_ptr<TiledMapResource> _tiledMapPtr;
		std::vector<TiledLayerData> _layersData;
	};
}

#endif //TILEDMAP2DRENDERERCOMPONENT_H

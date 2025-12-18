//
// Created by guillem on 6/20/25.
//

#ifndef TILEDMAP2DRENDERERCOMPONENT_H
#define TILEDMAP2DRENDERERCOMPONENT_H

#include <optional>

#include "Component.h"
#include "GEngine/Data/TiledLayerData.h"
#include "GEngine/Raylib/RaylibWrapper.h"
#include "GEngine/Data/CellPosition.h"
#include "GEngine/Extensions/Vec2Extensions.h"
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
		REGISTER_COMPONENT(TiledMap2dRendererComponent)

	public:
		explicit TiledMap2dRendererComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		void OnTick() override;
		void OnDrawSelectedGuizmo() override;

		void SetRenderLayer(std::int32_t layer) const;

		void SetTiledMap(const std::weak_ptr<TiledMapResource> &resource);
		[[nodiscard]] std::weak_ptr<TiledMapResource> GetTiledMap() const;

		[[nodiscard]] glm::i32vec2 GetMapGridSize() const;
		[[nodiscard]] int GetLayersCount() const;
		[[nodiscard]] bool HasTileAtGridPosition(std::int32_t layerIndex, const glm::i32vec2& gridPosition) const;

		[[nodiscard]] glm::vec2 GridPositionToWorldPosition(const glm::i32vec2& gridPosition, CellPosition cellPosition = CellPosition::CENTER) const;
		[[nodiscard]] glm::i32vec2 WorldPositionToGridPosition(const glm::vec2& worldPosition) const;

		[[nodiscard]] glm::vec2 GetWorldBounds() const;
		[[nodiscard]] glm::vec2 GetTileWorldSize() const;

		[[nodiscard]] std::int32_t GetTileLayerIndexFromName(const std::string& tileLayerName) const;

		void SetTileLayerVisible(std::int32_t layerIndex, bool visible);
		[[nodiscard]] bool GetIsTileLayerVisible(std::int32_t layerIndex) const;

		void SetTileLayerRenderLayerOffset(std::int32_t tileLayerIndex, std::int32_t renderLayerOffset);
		std::int32_t GetTileLayerRenderLayerOffset(std::int32_t tileLayerIndex) const;

		static glm::i32vec2 TiledGridPositionToEngineGridPosition(const tmx::TileLayer& tileLayer, glm::i32vec2 gridPosition);

		[[nodiscard]] static glm::vec2 GridPositionToWorldPosition(
			const glm::i32vec2& mapGridSize,
			const glm::vec2& tilePixelSize,
			const glm::vec2& tilemapPosition,
			float tilemapRotation,
			const glm::vec2& tilemapScale,
			const glm::i32vec2& gridPosition,
			CellPosition cellPosition = CellPosition::CENTER
			);

	private:
		void GenerateLayersData();

		[[nodiscard]] std::optional<std::reference_wrapper<const tmx::TileLayer>> GetTileLayer(std::int32_t layerIndex) const;

		void RenderLayerGrid(
			const TiledMapResource* tiledMapResource,
			const tmx::Map* mapData,
			const std::vector<tmx::TileLayer::Tile>& layerTileIds,
			const tmx::Vector2u& pixelSizeOfTile,
			const tmx::Vector2u& layerGridSize,
			const glm::vec2& position,
			float rotation,
			const glm::vec2& scale
			) const;

	private:
		std::shared_ptr<Property<std::int32_t>> _renderLayer;

		std::weak_ptr<TiledMapResource> _tiledMapPtr;
		std::vector<TiledLayerData> _tileLayersData;

		glm::vec2 _tilePixelSize = Vec2Extensions::Zero;
	};
}

#endif //TILEDMAP2DRENDERERCOMPONENT_H

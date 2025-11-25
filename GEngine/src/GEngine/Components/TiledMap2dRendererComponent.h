//
// Created by guillem on 6/20/25.
//

#ifndef TILEDMAP2DRENDERERCOMPONENT_H
#define TILEDMAP2DRENDERERCOMPONENT_H

#include <optional>

#include "Component.h"
#include "GEngine/Data/TiledLayerData.h"
#include "raylib.h"
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
	public:
		explicit TiledMap2dRendererComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		constexpr const char* GetTypeName() override { return "TiledMap2dRenderer"; }

		void OnTick() override;
		void OnDrawSelectedGuizmo(GuizmoUiRenderer *guizmoUiRenderer) override;

		void SetTiledMap(const std::weak_ptr<TiledMapResource> &resource);
		std::weak_ptr<TiledMapResource> GetTiledMap() const;

		glm::i32vec2 GetMapGridSize() const;
		int GetLayersCount() const;
		bool HasTileAtGridPosition(std::int32_t layerIndex, const glm::i32vec2& gridPosition) const;

		glm::vec2 GridPositionToWorldPosition(const glm::i32vec2& gridPosition, CellPosition cellPosition = CellPosition::BOTTOM_LEFT) const;
		glm::i32vec2 WorldPositionToGridPosition(const glm::vec2& worldPosition) const;

		void SetLayerVisible(std::int32_t layerIndex, bool visible);
		bool GetIsLayerVisible(std::int32_t layerIndex) const;

		static glm::i32vec2 TiledGridPositionToEngineGridPosition(const tmx::TileLayer& tileLayer, glm::i32vec2 gridPosition);

	private:
		void GenerateLayersData();

		std::optional<std::reference_wrapper<const tmx::TileLayer>> GetTileLayer(std::int32_t layerIndex) const;

		glm::vec2 GridPositionToWorldPosition(
			const glm::i32vec2& mapGridSize,
			glm::vec2 tilemapPosition,
			float tilemapRotation,
			glm::vec2 tilemapScale,
			const glm::i32vec2& gridPosition,
			CellPosition cellPosition = CellPosition::BOTTOM_LEFT
			) const;

		void RenderLayerGrid(
			const TiledMapResource* tiledMapResource,
			const tmx::Map* mapData,
			const std::vector<tmx::TileLayer::Tile>& layerTileIds,
			const tmx::Vector2u pixelSizeOfTile,
			const tmx::TileLayer& tileLayer,
			const tmx::Vector2u& layerGridSize,
			const glm::vec2& position,
			const float rotation,
			const glm::vec2& scale
			) const;

	private:
		std::weak_ptr<TiledMapResource> _tiledMapPtr;
		std::vector<TiledLayerData> _layersData;

		glm::vec2 _tilePixelSize = Vec2Extensions::Zero;
	};
}

#endif //TILEDMAP2DRENDERERCOMPONENT_H

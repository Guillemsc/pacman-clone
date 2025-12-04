//
// Created by guillem on 6/20/25.
//

#include "TiledMap2dRendererComponent.h"

#include <cmath>

#include "TransformComponent.h"
#include "GEngine/Data/TiledLayerData.h"
#include "GEngine/Extensions/MathExtensions.h"
#include "GEngine/Extensions/RayLibExtensions.h"
#include "GEngine/Extensions/Vec2Extensions.h"
#include "GEngine/Extensions/VectorExtensions.h"
#include "glm/vec2.hpp"
#include "GEngine/Modules/RenderingModule.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Rendering/GuizmoUiRenderer.h"
#include "GEngine/Rendering/Renderer2d.h"
#include "GEngine/Rendering/UiRenderer.h"
#include "GEngine/Resources/TextureResource.h"
#include "GEngine/Resources/TiledMapResource.h"
#include "tmxlite/TileLayer.hpp"

namespace GEngine
{
	TiledMap2dRendererComponent::TiledMap2dRendererComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity)
	: Component(modules, entity)
	{
	}

	void TiledMap2dRendererComponent::OnTick()
	{
		const std::shared_ptr<TiledMapResource> tiledMap = _tiledMapPtr.lock();
		if (!tiledMap) return;

		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (entity == nullptr) return;

		const std::shared_ptr<TransformComponent> transform = entity->GetTransform().lock();
		if (transform == nullptr) return;

		const std::shared_ptr<tmx::Map> rawMap = tiledMap->GetRawMap().lock();
		if (!rawMap) return;

		glm::vec2 position = transform->GetPositionXY();
		float rotation = transform->GetRotationEulerZ();
		glm::vec2 scale = transform->GetScaleXY();

		modules->rendering->Render2d()->Add(0, [rawMap, position, scale, rotation, this, tiledMap]
		{
			const tmx::Vector2u pixelSizeOfTile = rawMap->getTileSize();
			const tmx::Vector2u mapGridSize = rawMap->getTileCount();
			const std::vector<tmx::Layer::Ptr>& layers = rawMap->getLayers();

			if (pixelSizeOfTile.x == 0 || pixelSizeOfTile.y == 0) return;

			for (int i = 0; i < layers.size(); ++i)
			{
				const auto& layer = layers[i];

				if (layer->getType() != tmx::Layer::Type::Tile) continue;

				const bool isVisible = GetIsLayerVisible(i);
				if (!isVisible) continue;

				const tmx::TileLayer& tileLayer = layer->getLayerAs<tmx::TileLayer>();

				const std::vector<tmx::TileLayer::Tile>& tileIds = tileLayer.getTiles();

				RenderLayerGrid(
					tiledMap.get(),
					rawMap.get(),
					tileIds,
					pixelSizeOfTile,
					mapGridSize,
					position,
					rotation,
					scale
				);
			}
		});
	}

	void TiledMap2dRendererComponent::OnDrawSelectedGuizmo()
	{
		Guizmo2dRenderer* guizmoRenderer = modules->rendering->Guizmo2dRender();

		const std::shared_ptr<TiledMapResource> tiledMap = _tiledMapPtr.lock();
		if (!tiledMap) return;

		const std::shared_ptr<tmx::Map> rawMap = tiledMap->GetRawMap().lock();
		if (!rawMap) return;

		const std::shared_ptr<TransformComponent> transform = GetEntity().lock()->GetTransform().lock();
		if (!transform) return;

		const float rotationRadians = transform->GetRotationEulerZ();

		const glm::vec2 tileWorldSize = GetTileWorldSize();
		const tmx::Vector2u mapGridSize = rawMap->getTileCount();

		for (int x = 0; x < mapGridSize.x; x++)
		{
			for (int y = 0; y < mapGridSize.y; y++)
			{
				const glm::i32vec2 girdPosition = tiledMap->TiledGridPositionToEngineGridPosition({ x, y });

				glm::vec2 worldPosition = GridPositionToWorldPosition(girdPosition, CellPosition::CENTER);

				guizmoRenderer->AddRect(worldPosition, {1, 1}, 0, Color01::Blue);
				guizmoRenderer->AddRectLines(worldPosition, tileWorldSize, rotationRadians, 0.5f, Color01::Green);
			}
		}
	}

	void TiledMap2dRendererComponent::SetTiledMap(const std::weak_ptr<TiledMapResource> &resource)
	{
		_tiledMapPtr = resource;

		GenerateLayersData();
	}

	std::weak_ptr<TiledMapResource> TiledMap2dRendererComponent::GetTiledMap() const
	{
		return _tiledMapPtr;
	}

	int TiledMap2dRendererComponent::GetLayersCount() const
	{
		const std::shared_ptr<TiledMapResource> tiledMap = _tiledMapPtr.lock();
		if (!tiledMap) return 0;

		const std::shared_ptr<tmx::Map> mapData = tiledMap->GetRawMap().lock();
		if (!mapData) return 0;

		return mapData->getLayers().size();
	}

	glm::i32vec2 TiledMap2dRendererComponent::GetMapGridSize() const
	{
		const std::shared_ptr<TiledMapResource> tiledMap = _tiledMapPtr.lock();
		if (!tiledMap) return Vec2Extensions::Int32Zero;

		const std::shared_ptr<tmx::Map> rawMap = tiledMap->GetRawMap().lock();
		if (!rawMap) return Vec2Extensions::Int32Zero;

		const tmx::Vector2u mapGridSize = rawMap->getTileCount();

		return { mapGridSize.x, mapGridSize.y };
	}

	bool TiledMap2dRendererComponent::HasTileAtGridPosition(const std::int32_t layerIndex, const glm::i32vec2 &gridPosition) const
	{
		const auto optionalLayer = GetTileLayer(layerIndex);
		if (!optionalLayer) return false;
		const tmx::TileLayer& tileLayer = optionalLayer->get();

		const glm::i32vec2 layerGridSize = { tileLayer.getSize().x,  tileLayer.getSize().y};

		if (gridPosition.x < 0 || gridPosition.x >= layerGridSize.x || gridPosition.y < 0 || gridPosition.y >= layerGridSize.y) return false;

		const std::vector<tmx::TileLayer::Tile>& tileIds = tileLayer.getTiles();

		const glm::i32vec2 goodGridPosition = TiledGridPositionToEngineGridPosition(tileLayer, gridPosition);
		const std::int32_t tileIdIndex = goodGridPosition.y * layerGridSize.x + goodGridPosition.x;

		const bool outsideTileIdsBounds = tileIdIndex < 0 || tileIdIndex >= tileIds.size();

		if (outsideTileIdsBounds) return false;

		return tileIds[tileIdIndex].ID != 0;
	}

	glm::vec2 TiledMap2dRendererComponent::GridPositionToWorldPosition(
		const glm::i32vec2& gridPosition,
		const CellPosition cellPosition
		) const
	{
		const std::shared_ptr<TiledMapResource> tiledMap = _tiledMapPtr.lock();
		if (!tiledMap) return Vec2Extensions::Zero;

		const std::shared_ptr<tmx::Map> mapData = tiledMap->GetRawMap().lock();
		if (!mapData) return Vec2Extensions::Zero;

		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (entity == nullptr) return Vec2Extensions::Zero;

		const std::shared_ptr<TransformComponent> transform = entity->GetTransform().lock();
		if (transform == nullptr) return Vec2Extensions::Zero;

		if (_tilePixelSize.x == 0 || _tilePixelSize.y == 0) return Vec2Extensions::Zero;

		const glm::i32vec2 mapGridSize = { mapData->getTileCount().x, mapData->getTileCount().y };

		const glm::vec2 position = transform->GetPositionXY();
		const float rotation = transform->GetRotationEulerZ();
		const glm::vec2 scale = transform->GetScaleXY();

		return GridPositionToWorldPosition(
			mapGridSize,
			position,
			rotation,
			scale,
			gridPosition,
			cellPosition
		);
	}

	glm::i32vec2 TiledMap2dRendererComponent::WorldPositionToGridPosition(
		const glm::vec2 &worldPosition
		) const
	{
		const std::shared_ptr<TiledMapResource> tiledMap = _tiledMapPtr.lock();
		if (!tiledMap) return Vec2Extensions::Int32Zero;

		const std::shared_ptr<tmx::Map> mapData = tiledMap->GetRawMap().lock();
		if (!mapData) return Vec2Extensions::Int32Zero;

		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (entity == nullptr) return Vec2Extensions::Int32Zero;

		const std::shared_ptr<TransformComponent> transform = entity->GetTransform().lock();
		if (transform == nullptr) return Vec2Extensions::Int32Zero;

		const glm::vec2 position = transform->GetPositionXY();
		const float rotation = transform->GetRotationEulerZ();
		const glm::vec2 scale = transform->GetScaleXY();

		const glm::vec2 layerGridSize = { mapData->getTileCount().x, mapData->getTileCount().y };
		const glm::vec2 layerPixelSize = layerGridSize * _tilePixelSize;
		const glm::vec2 layerPixelSizeScaled = { layerPixelSize.x * scale.x, layerPixelSize.y * scale.y };

		const float layerStartPositionX = position.x - (layerPixelSizeScaled.x * 0.5f);
		const float layerStartPositionY = position.y - (layerPixelSizeScaled.y * 0.5f);

		const glm::vec2 layerStartPosition = {layerStartPositionX, layerStartPositionY};
		const glm::vec2 layerEndPosition = layerStartPosition + layerPixelSizeScaled;
		const glm::vec2 pivot = position;

		const glm::vec2 finalPosition = MathExtensions::InverseRotatePointAroundPivot(worldPosition, pivot, rotation);

		glm::vec2 normalizedPosition = Vec2Extensions::GetNormalizedValue(finalPosition, layerStartPosition, layerEndPosition);

		const glm::vec2 localNormalisedPosition = {layerGridSize.x * normalizedPosition.x, layerGridSize.y * normalizedPosition.y};

		return localNormalisedPosition;
	}

	glm::vec2 TiledMap2dRendererComponent::GetTileWorldSize() const
	{
		const std::shared_ptr<TransformComponent> transform = GetEntity().lock()->GetTransform().lock();

		const glm::vec2 scale = transform->GetScaleXY();

		return _tilePixelSize * scale;
	}

	std::int32_t TiledMap2dRendererComponent::GetLayerNameFromLayerIndex(const std::string &layerName) const
	{
		const std::shared_ptr<TiledMapResource> tiledMap = _tiledMapPtr.lock();
		if (!tiledMap) return -1;

		return tiledMap->GetLayerIndexFromLayerName(layerName);
	}

	void TiledMap2dRendererComponent::SetLayerVisible(const std::int32_t layerIndex, const bool visible)
	{
		if (VectorExtensions::IsIndexOutsideBounds(_layersData, layerIndex)) return;

		_layersData[layerIndex].Visible = visible;
	}

	bool TiledMap2dRendererComponent::GetIsLayerVisible(const std::int32_t layerIndex) const
	{
		return VectorExtensions::GetOrDefault(_layersData, layerIndex, TiledLayerData::Default).Visible;
	}

	glm::i32vec2 TiledMap2dRendererComponent::TiledGridPositionToEngineGridPosition(
		const tmx::TileLayer& tileLayer,
		const glm::i32vec2 gridPosition
	)
	{
		const tmx::Vector2 layerGridSize = tileLayer.getSize();
		const std::int32_t gridPositionY = layerGridSize.y - gridPosition.y - 1;
		return { gridPosition.x, gridPositionY };
	}

	void TiledMap2dRendererComponent::GenerateLayersData()
	{
		_layersData.clear();

		const std::shared_ptr<TiledMapResource> tiledMap = _tiledMapPtr.lock();
		if (!tiledMap) return;

		const std::shared_ptr<tmx::Map> mapData = tiledMap->GetRawMap().lock();
		if (!mapData) return;

		const std::vector<tmx::Layer::Ptr>& layers = mapData->getLayers();

		for (const auto& layer : layers)
		{
			if (layer->getType() != tmx::Layer::Type::Tile)
			{
				continue;
			}

			TiledLayerData layerData;

			_layersData.push_back(layerData);
		}

		_tilePixelSize = { mapData->getTileSize().x, mapData->getTileSize().y };
	}

	std::optional<std::reference_wrapper<const tmx::TileLayer>> TiledMap2dRendererComponent::GetTileLayer(const std::int32_t layerIndex) const
	{
		const std::shared_ptr<TiledMapResource> tiledMap = _tiledMapPtr.lock();
		if (!tiledMap) return std::nullopt;

		return tiledMap->GetTileLayer(layerIndex);
	}

	glm::vec2 TiledMap2dRendererComponent::GridPositionToWorldPosition(
		const glm::i32vec2& mapGridSize,
		const glm::vec2 tilemapPosition,
		const float tilemapRotation,
		const glm::vec2 tilemapScale,
		const glm::i32vec2& gridPosition,
		const CellPosition cellPosition
		) const
	{
		if (_tilePixelSize.x == 0 || _tilePixelSize.y == 0) return Vec2Extensions::Zero;

		const glm::vec2 layerGridSize = { mapGridSize.x, mapGridSize.y };
		const glm::vec2 layerPixelSize = layerGridSize * _tilePixelSize;
		const glm::vec2 layerPixelSizeScaled = { layerPixelSize.x * tilemapScale.x, layerPixelSize.y * tilemapScale.y };

		const float layerStartPositionX = tilemapPosition.x - (layerPixelSizeScaled.x * 0.5f);
		const float layerStartPositionY = tilemapPosition.y - (layerPixelSizeScaled.y * 0.5f);

		float tilePositionX = layerStartPositionX + (static_cast<float>(gridPosition.x) * _tilePixelSize.x * tilemapScale.x);
		float tilePositionY = layerStartPositionY + (static_cast<float>(gridPosition.y) * _tilePixelSize.y * tilemapScale.y);

		if (cellPosition == CellPosition::CENTER)
		{
			tilePositionX += _tilePixelSize.x * 0.5f * tilemapScale.x;
			tilePositionY += _tilePixelSize.y * 0.5f * tilemapScale.y;
		}

		if (cellPosition == CellPosition::CENTER_RIGHT)
		{
			tilePositionX += _tilePixelSize.x * tilemapScale.x;
			tilePositionY += _tilePixelSize.y * 0.5f * tilemapScale.y;
		}

		const glm::vec2 point = { tilePositionX, tilePositionY };
		const glm::vec2 pivot = tilemapPosition;
		const glm::vec2 finalPosition = MathExtensions::RotatePointAroundPivot(point, pivot, -tilemapRotation);

		return finalPosition;
	}

	void TiledMap2dRendererComponent::RenderLayerGrid(
		const TiledMapResource* tiledMapResource,
		const tmx::Map* mapData,
		const std::vector<tmx::TileLayer::Tile> &layerTileIds,
		const tmx::Vector2u& pixelSizeOfTile,
		const tmx::Vector2u& layerGridSize,
		const glm::vec2& position,
		const float rotation,
		const glm::vec2& scale
		) const
	{
		const std::vector<tmx::Tileset>& tileSets = mapData->getTilesets();

		for (std::int32_t y = 0; y < layerGridSize.y; ++y)
		{
			for (std::int32_t x = 0; x < layerGridSize.x; ++x)
			{
				const std::int32_t tileIdIndex = y * layerGridSize.x + x;

				const bool outsideTileIdsBounds = tileIdIndex >= layerTileIds.size();
				if (outsideTileIdsBounds) continue;

				const std::uint32_t tileId = layerTileIds[tileIdIndex].ID;

				const int tileSetIndex = tiledMapResource->GetTilesetIndexForTileId(tileId);

				if (VectorExtensions::IsIndexOutsideBounds(tileSets, tileSetIndex)) continue;

				const tmx::Tileset& tileSet = tileSets[tileSetIndex];
				const std::uint32_t tileSetMargin = tileSet.getMargin();
				const std::uint32_t tileSetSpacing = tileSet.getSpacing();
				const std::uint32_t tileSetFirstGid = tileSet.getFirstGID();
				const std::uint32_t tileSetTileCount = tileSet.getTileCount();

				const bool insideBounds = tileId >= tileSetFirstGid
					&& tileId < tileSetFirstGid + tileSetTileCount;

				if (!insideBounds)
				{
					continue;
				}

				const std::shared_ptr<TextureResource> tileSetTexture = tiledMapResource->GetTilesetTexture(tileSetIndex).lock();
				if (!tileSetTexture) continue;

				const Texture2D& rawTexture = tileSetTexture->GetRawTexture();

				const tmx::Vector2 textureSize = { rawTexture.width, rawTexture.height };

				const std::int32_t tileSetGridSizeX = MathExtensions::SafeDivide(
					textureSize.x - (2 * tileSetMargin) + tileSetSpacing,
					pixelSizeOfTile.x + tileSetSpacing
					);

				const std::int32_t idIndex = tileId - tileSet.getFirstGID();
				const float tileNormalizedPositionOnTileSetX = static_cast<float>(idIndex % tileSetGridSizeX);
				const float tileNormalizedPositionOnTileSetY = static_cast<float>(idIndex / tileSetGridSizeX);

				const float tileStartOnTileSetTextureX = tileSetMargin + tileNormalizedPositionOnTileSetX * (pixelSizeOfTile.x + tileSetSpacing);
				const float tileStartOnTileSetTextureY = tileSetMargin + tileNormalizedPositionOnTileSetY * (pixelSizeOfTile.y + tileSetSpacing);

				const glm::i32vec2 girdPosition = tiledMapResource->TiledGridPositionToEngineGridPosition({ x, y });

				const glm::vec2 finalPosition = GridPositionToWorldPosition(
					{ layerGridSize.x, layerGridSize.y },
					position,
					rotation,
					scale,
					girdPosition,
					CellPosition::CENTER
					);

				Rectangle source = {
					tileStartOnTileSetTextureX,
					tileStartOnTileSetTextureY,
					static_cast<float>(pixelSizeOfTile.x),
					static_cast<float>(pixelSizeOfTile.y)
				};

				Renderer2d::DrawTexture(
					rawTexture,
					source,
					finalPosition,
					rotation,
					scale,
					Color01::White
					);
			}
		}
	}
} // GEngineCore
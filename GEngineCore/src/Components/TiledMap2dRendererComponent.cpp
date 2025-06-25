//
// Created by guillem on 6/20/25.
//

#include "TiledMap2dRendererComponent.h"

#include <cmath>

#include "TransformComponent.h"
#include "Extensions/MathExtensions.h"
#include "Extensions/RayLibExtensions.h"
#include "Extensions/VectorExtensions.h"
#include "glm/vec2.hpp"
#include "Modules/RenderingModule.h"
#include "Modules/ResourcesModule.h"
#include "Resources/TextureResource.h"
#include "Resources/TiledMapResource.h"
#include "tmxlite/TileLayer.hpp"

namespace GEngineCore
{
	TiledMap2dRendererComponent::TiledMap2dRendererComponent(const std::weak_ptr<Entity> &entity) : Component(entity)
	{
	}

	void TiledMap2dRendererComponent::OnTick()
	{
		const std::shared_ptr<TiledMapResource> tiledMap = _tiledMapPtr.lock();
		if (!tiledMap) return;

		const std::shared_ptr<GEngineCoreApplication> app = GetApp().lock();
		if (app == nullptr) return;

		const std::shared_ptr<RenderingModule> rendering = app->Rendering().lock();
		if (rendering == nullptr) return;

		const std::shared_ptr<ResourcesModule> resources = app->Resources().lock();
		if (resources == nullptr) return;

		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (entity == nullptr) return;

		const std::shared_ptr<TransformComponent> transform = entity->GetTransform().lock();
		if (transform == nullptr) return;

		const std::shared_ptr<tmx::Map> rawMap = tiledMap->GetRawMap().lock();
		if (!rawMap) return;

		glm::vec2 position = transform->GetPositionXY();
		float rotation = transform->GetRotationEulerZ();
		glm::vec2 scale = transform->GetScaleXY();

		rendering->Render2D().lock()->Add(0, [resources, rawMap, position, scale, rotation, this, tiledMap]
		{
			const tmx::Vector2u pixelSizeOfTile = rawMap->getTileSize();
			const std::vector<tmx::Tileset>& tileSets = rawMap->getTilesets();
			const std::vector<tmx::Layer::Ptr>& layers = rawMap->getLayers();

			if (pixelSizeOfTile.x == 0 || pixelSizeOfTile.y == 0)
			{
				return;
			}

			std::int32_t layerIndex = 0;

			for (const auto& layer : layers)
			{
				if (layer->getType() != tmx::Layer::Type::Tile)
				{
					continue;
				}

				const bool isVisible = GetIsLayerVisible(layerIndex);

				if (!isVisible)
				{
					++layerIndex;
					continue;
				}

				const tmx::TileLayer& tileLayer = layer->getLayerAs<tmx::TileLayer>();
				const tmx::Vector2u layerGridSize = tileLayer.getSize();

				const std::vector<tmx::TileLayer::Tile>& tileIds  = tileLayer.getTiles();

				RenderLayerGrid(
					resources.get(),
					tiledMap.get(),
					rawMap.get(),
					tileIds,
					pixelSizeOfTile,
					tileLayer,
					layerGridSize,
					position,
					rotation,
					scale
				);

				++layerIndex;
			}
		});
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

	glm::i32vec2 TiledMap2dRendererComponent::GetLayerGridSize(const std::int32_t layerIndex) const
	{
		const std::shared_ptr<TiledMapResource> tiledMap = _tiledMapPtr.lock();
		if (!tiledMap) return glm::i32vec2(0);

		const std::shared_ptr<tmx::Map> mapData = tiledMap->GetRawMap().lock();
		if (!mapData) return glm::i32vec2(0);

		const std::vector<tmx::Layer::Ptr>& layers = mapData->getLayers();

		if (VectorExtensions::IsIndexOutsideBounds(layers, layerIndex)) return glm::i32vec2(0);

		const tmx::Layer::Ptr& layer = layers[layerIndex];
		const tmx::TileLayer& tileLayer = layer->getLayerAs<tmx::TileLayer>();

		const tmx::Vector2u layerTileSize = tileLayer.getSize();

		return { layerTileSize.x, layerTileSize.y };
	}

	glm::vec2 TiledMap2dRendererComponent::GridPositionToWorldPosition(
		const std::int32_t layerIndex,
		const std::int32_t x,
		const std::int32_t y
		) const
	{
		const std::shared_ptr<TiledMapResource> tiledMap = _tiledMapPtr.lock();
		if (!tiledMap) return glm::vec2(0);

		const std::shared_ptr<tmx::Map> mapData = tiledMap->GetRawMap().lock();
		if (!mapData) return glm::vec2(0);

		const std::vector<tmx::Layer::Ptr>& layers = mapData->getLayers();

		if (VectorExtensions::IsIndexOutsideBounds(layers, layerIndex)) return glm::vec2(0);

		const tmx::Layer::Ptr& layer = layers[layerIndex];

		if (layer->getType() != tmx::Layer::Type::Tile) return glm::vec2(0);

		const tmx::TileLayer& tileLayer = layer->getLayerAs<tmx::TileLayer>();

		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (entity == nullptr) return glm::vec2(0);

		const std::shared_ptr<TransformComponent> transform = entity->GetTransform().lock();
		if (transform == nullptr) return glm::vec2(0);

		const tmx::Vector2u pixelSizeOfTile = mapData->getTileSize();

		if (pixelSizeOfTile.x == 0 || pixelSizeOfTile.y == 0) return glm::vec2(0);

		const glm::vec2 position = transform->GetPositionXY();
		const float rotation = transform->GetRotationEulerZ();
		const glm::vec2 scale = transform->GetScaleXY();

		return GridPositionToWorldPosition(
			tileLayer,
			position,
			rotation,
			scale,
			mapData.get(),
			x,
			y
		);
	}

	void TiledMap2dRendererComponent::SetLayerVisible(const std::int32_t layerIndex, const bool visible)
	{
		if (VectorExtensions::IsIndexOutsideBounds(_canDrawLayerSettings, layerIndex)) return;

		_canDrawLayerSettings[layerIndex] = visible;
	}

	bool TiledMap2dRendererComponent::GetIsLayerVisible(const std::int32_t layerIndex) const
	{
		return VectorExtensions::GetOrDefault(_canDrawLayerSettings, layerIndex, false);
	}

	void TiledMap2dRendererComponent::GenerateLayersData()
	{
		_canDrawLayerSettings.clear();

		const std::shared_ptr<TiledMapResource> tiledMap = _tiledMapPtr.lock();
		if (!tiledMap);

		const std::shared_ptr<tmx::Map> mapData = tiledMap->GetRawMap().lock();
		if (!mapData);

		const std::vector<tmx::Layer::Ptr>& layers = mapData->getLayers();

		for (const auto& layer : layers)
		{
			if (layer->getType() != tmx::Layer::Type::Tile)
			{
				continue;
			}

			_canDrawLayerSettings.push_back(true);
		}
	}

	glm::vec2 TiledMap2dRendererComponent::GridPositionToWorldPosition(
		const tmx::TileLayer &tileLayer,
		const glm::vec2 tilemapPosition,
		const float tilemapRotation,
		const glm::vec2 tilemapScale,
		const tmx::Map *mapData,
		const std::int32_t x,
		const std::int32_t y
		)
	{
		const tmx::Vector2u pixelSizeOfTile = mapData->getTileSize();

		if (pixelSizeOfTile.x == 0 || pixelSizeOfTile.y == 0) return glm::vec2(0);

		const tmx::Vector2u layerGridSize = tileLayer.getSize();
		const tmx::Vector2u layerPixelSize = layerGridSize * pixelSizeOfTile;
		const glm::vec2 layerPixelSizeScaled = { layerPixelSize.x * tilemapScale.x, layerPixelSize.y * tilemapScale.y };

		const float layerStartPositionX = tilemapPosition.x - (layerPixelSizeScaled.x * 0.5f);
		const float layerStartPositionY = tilemapPosition.y - (layerPixelSizeScaled.y * 0.5f);

		const float layerCenterPositionX = layerStartPositionX + (layerPixelSizeScaled.x * 0.5f);
		const float layerCenterPositionY = layerStartPositionY + (layerPixelSizeScaled.y * 0.5f);

		const float tilePositionX = layerStartPositionX + (static_cast<float>(x) * pixelSizeOfTile.x * tilemapScale.x);
		const float tilePositionY = layerStartPositionY + (static_cast<float>(y) * pixelSizeOfTile.y * tilemapScale.y);

		const glm::vec2 point = { tilePositionX, tilePositionY };
		const glm::vec2 pivot = { layerCenterPositionX, layerCenterPositionY };
		const glm::vec2 finalPosition = MathExtensions::RotatePointAroundPivot(point, pivot, tilemapRotation);

		return finalPosition;
	}

	void TiledMap2dRendererComponent::RenderLayerGrid(
		const ResourcesModule* resourcesModule,
		const TiledMapResource* tiledMapResource,
		const tmx::Map* mapData,
		const std::vector<tmx::TileLayer::Tile> &layerTileIds,
		const tmx::Vector2u pixelSizeOfTile,
		const tmx::TileLayer& tileLayer,
		const tmx::Vector2u &layerGridSize,
		const glm::vec2& position,
		const float rotation,
		const glm::vec2& scale
		)
	{
		const std::vector<tmx::Tileset>& tileSets = mapData->getTilesets();

		const float rotationDegrees = glm::degrees(rotation);

		for (std::int32_t y = 0; y < layerGridSize.y; ++y)
		{
			for (std::int32_t x = 0; x < layerGridSize.x; ++x)
			{
				const std::int32_t tileIdIndex = y * layerGridSize.x + x;

				const bool outsideTileIdsBounds = tileIdIndex >= layerTileIds.size();

				if (outsideTileIdsBounds)
				{
					continue;
				}

				const std::uint32_t tileId = layerTileIds[tileIdIndex].ID;

				const int tilesetIndex = tiledMapResource->GetTilesetIndexForTileID(tileId);

				if (VectorExtensions::IsIndexOutsideBounds(tileSets, tilesetIndex)) continue;

				const tmx::Tileset& tileSet = tileSets[tilesetIndex];
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

				const std::string& imagePath = tileSet.getImagePath();
				std::string resourcesImagePath = resourcesModule->FullPathToRelativeResourcesPath(imagePath);
				const std::shared_ptr<TextureResource> tilesetTexture = resourcesModule->GetResource<TextureResource>(resourcesImagePath).lock();

				if (!tilesetTexture) continue;

				const Texture2D& rawTexture = tilesetTexture->GetRawTexture();

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

				const glm::vec2 finalPosition = GridPositionToWorldPosition(
					tileLayer,
					position,
					rotation,
					scale,
					mapData,
					x,
					y
					);

				Rectangle source = {
					tileStartOnTileSetTextureX,
					tileStartOnTileSetTextureY,
					static_cast<float>(pixelSizeOfTile.x),
					static_cast<float>(pixelSizeOfTile.y)
				};

				RayLibExtensions::DrawTextureEx(
					rawTexture,
					source,
					{ finalPosition.x, finalPosition.y },
					rotationDegrees,
					{ scale.x, scale.y },
					WHITE
					);
			}
		}
	}
} // GEngineCore
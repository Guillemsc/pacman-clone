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
		float rotationDegrees = transform->GetRotationEulerDegreesZ();
		glm::vec2 scale = transform->GetScaleXY();

		rendering->Render2D().lock()->Add(0, [resources, rawMap, position, scale, rotationDegrees, rotation]
		{
			const tmx::Vector2u pixelSizeOfTile = rawMap->getTileSize();
			const std::vector<tmx::Tileset>& tileSets = rawMap->getTilesets();
			const std::vector<tmx::Layer::Ptr>& layers = rawMap->getLayers();

			if (pixelSizeOfTile.x == 0 || pixelSizeOfTile.y == 0)
			{
				return;
			}

			for (const auto& layer : layers)
			{
				if (layer->getType() != tmx::Layer::Type::Tile)
				{
					continue;
				}

				const tmx::TileLayer& tileLayer = layer->getLayerAs<tmx::TileLayer>();

				const tmx::Vector2u layerGridSize = tileLayer.getSize();

				for (auto i = 0u; i < tileSets.size(); ++i)
				{
					const tmx::Tileset& tileSet = tileSets[i];
					const std::uint32_t margin = tileSet.getMargin();
					const std::uint32_t spacing = tileSet.getSpacing();
					const std::vector<tmx::TileLayer::Tile>& tileIds  = tileLayer.getTiles();

					const std::string& imagePath = tileSet.getImagePath();
					std::string resourcesImagePath = resources->FullPathToRelativeResourcesPath(imagePath);
					const std::shared_ptr<TextureResource> tilesetTexture = resources->GetResource<TextureResource>(resourcesImagePath).lock();

					if (!tilesetTexture) continue;

					const Texture2D& rawTexture = tilesetTexture->GetRawTexture();

					const tmx::Vector2 textureSize = { rawTexture.width, rawTexture.height };

					const std::int32_t tileSetGridSizeX = (textureSize.x - (2 * margin) + spacing) / (pixelSizeOfTile.x + spacing);

					for (std::int32_t y = 0u; y < layerGridSize.y; ++y)
					{
						for (std::int32_t x = 0u; x < layerGridSize.x; ++x)
						{
							const std::int32_t tileIdIndex = y * layerGridSize.x + x;

							const bool insideBounds = tileIdIndex < tileIds.size()
								&& tileIds[tileIdIndex].ID >= tileSet.getFirstGID()
								&& tileIds[tileIdIndex].ID < tileSet.getFirstGID() + tileSet.getTileCount();

							if (!insideBounds)
							{
								continue;
							}

							const std::int32_t idIndex = tileIds[tileIdIndex].ID - tileSet.getFirstGID();
							const float tileNormalizedPositionOnTileSetX = static_cast<float>(idIndex % tileSetGridSizeX);
							const float tileNormalizedPositionOnTileSetY = static_cast<float>(idIndex / tileSetGridSizeX);

							const float tileStartOnTileSetTextureX = margin + tileNormalizedPositionOnTileSetX * (pixelSizeOfTile.x + spacing);
							const float tileStartOnTileSetTextureY = margin + tileNormalizedPositionOnTileSetY * (pixelSizeOfTile.y + spacing);

							const glm::vec2 finalPosition = GridPositionToWorldPosition(
								tileLayer,
								position,
								rotation,
								scale,
								rawMap.get(),
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
								{finalPosition.x, finalPosition.y},
								rotationDegrees,
								{scale.x, scale.y},
								WHITE
								);
						}
					}
				}
			}
		});
	}

	void TiledMap2dRendererComponent::SetTiledMap(const std::weak_ptr<TiledMapResource> &resource)
	{
		_tiledMapPtr = resource;
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
} // GEngineCore
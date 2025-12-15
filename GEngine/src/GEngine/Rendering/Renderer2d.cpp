//
// Created by guillem on 6/8/25.
//

#include "Renderer2d.h"

#include "GEngine/Raylib/RaylibWrapper.h"
#include "GEngine/Cameras/Camera.h"
#include "GEngine/Components/TiledMap2dRendererComponent.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Data/CellPosition.h"
#include "GEngine/Extensions/Color01Extensions.h"
#include "GEngine/Extensions/VectorExtensions.h"
#include "GEngine/Modules/WindowModule.h"
#include "GEngine/Resources/TextureResource.h"
#include "tmxlite/TileLayer.hpp"

namespace GEngine
{
	Renderer2d::Renderer2d(GEngineCoreModules *modules)
		: _modules(modules)
	{
	}

	void Renderer2d::Render()
	{
		for (auto it = _queue.begin(); it != _queue.end(); ++it)
		{
			const std::vector<Renderer2dCommand>& commands = it->second;

			for (auto commandIt = commands.begin(); commandIt != commands.end(); ++commandIt)
			{
				const Renderer2dCommand& command = *commandIt;
				RenderCommand(command);
			}

			it->second.clear();
		}
	}

	void Renderer2d::AddTexture(
		const std::int32_t layer,
		const Texture2D &texture,
		const rlRectangle &source,
		const glm::vec2& position,
		const float rotationRadians,
		const glm::vec2& scale,
		const Color01& color
		)
	{
		AddCommand(
			layer,
			Renderer2dCommand {
				.type = Renderer2dCommandType::TEXTURE,
				.texture =  {
					texture,
					source,
					position,
					rotationRadians,
					scale,
					color
				}
			});
	}

	void Renderer2d::AddRect(
		const std::int32_t layer,
		const glm::vec2 &position,
		const float rotationRadians,
		const glm::vec2 &scale,
		const glm::vec2& size,
		const Color01 &color
		)
	{
		AddCommand(
			layer,
			Renderer2dCommand {
				.type = Renderer2dCommandType::RECT,
				.rect =  {
					position,
					rotationRadians,
					scale,
					size,
					color
				}
			});
	}

	void Renderer2d::AddTiledLayer(
		const std::int32_t layer,
		TiledMapResource* tiledMapResource,
		const int layerIndex,
		const glm::vec2 &position,
		const float rotationRadians,
		const glm::vec2 &scale
		)
	{
		AddCommand(
			layer,
			Renderer2dCommand {
				.type = Renderer2dCommandType::TILED_LAYER,
				.tiledLayer =  {
					tiledMapResource,
					layerIndex,
					position,
					rotationRadians,
					scale
				}
			});
	}

	void Renderer2d::DrawTexture(
		const Texture2D &texture,
		const rlRectangle &source,
		const glm::vec2 &position,
		const float rotationRadians,
		const glm::vec2 &scale,
		const Color01 &color
		)
	{
		const glm::vec2 renderPosition = PositionToRenderPosition(position);
		const float rotationDegrees = RotationToRenderRotation(glm::degrees(rotationRadians));
		const Vector2 size = { source.width * scale.x, source.height * scale.y };
		const Vector2 center = { size.x * 0.5f, size.y * 0.5f };
		const rlRectangle dest = { renderPosition.x, renderPosition.y, size.x, size.y };
		const Color raylibColor = Color01Extensions::ToRaylibColor(color);

		DrawTexturePro(texture, source, dest, center, rotationDegrees, raylibColor);
	}

	glm::vec2 Renderer2d::PositionToRenderPosition(const glm::vec2 &position)
	{
		const glm::vec2 newPosition = { position.x, -position.y };
		return newPosition;
	}

	float Renderer2d::RotationToRenderRotation(const float rotation)
	{
		return -rotation;
	}

	void Renderer2d::AddCommand(const std::int32_t layer, const Renderer2dCommand &command)
	{
		_queue[layer].push_back(command);
	}

	void Renderer2d::RenderCommand(const Renderer2dCommand &command)
	{
		switch (command.type)
		{
			case Renderer2dCommandType::TEXTURE:
			{
				RenderTextureCommand(command.texture);
				break;
			}

			case Renderer2dCommandType::RECT:
			{
				RenderRectCommand(command.rect);
				break;
			}

			case Renderer2dCommandType::TILED_LAYER:
			{
				RenderTiledLayerCommand(command.tiledLayer);
				break;
			}
		}
	}

	void Renderer2d::RenderTextureCommand(const TextureRenderer2dCommand &command)
	{
		const glm::vec2 renderPosition = PositionToRenderPosition(command.position);
		const float rotationDegrees = RotationToRenderRotation(glm::degrees(command.rotationRadians));
		const glm::vec2 size = { std::abs(command.source.width * command.scale.x), std::abs(command.source.height * command.scale.y) };
		const Vector2 center = { size.x * 0.5f, size.y * 0.5f };
		const Color raylibColor = Color01Extensions::ToRaylibColor(command.color);

		const rlRectangle rectangle = {
			renderPosition.x,
			renderPosition.y,
			size.x,
			size.y,
		};

		DrawTexturePro(command.texture, command.source, rectangle, center, rotationDegrees, raylibColor);
	}

	void Renderer2d::RenderRectCommand(const RectRenderer2dCommand &command)
	{
		const glm::vec2 renderPosition = PositionToRenderPosition(command.position);
		const float rotationDegrees = RotationToRenderRotation(glm::degrees(command.rotationRadians));
		const glm::vec2 size = { command.size.x * command.scale.x, command.size.y * command.scale.y };
		const Vector2 center = { size.x * 0.5f, size.y * 0.5f };
		const Color raylibColor = Color01Extensions::ToRaylibColor(command.color);

		const rlRectangle rectangle = {
			renderPosition.x,
			renderPosition.y,
			size.x,
			size.y,
		};

		DrawRectanglePro(rectangle, center, rotationDegrees, raylibColor);
	}

	void Renderer2d::RenderTiledLayerCommand(
		const TiledLayerRenderer2dCommand &command
		)
	{
		const std::shared_ptr<tmx::Map> mapData = command.tiledMapResource->GetRawMap().lock();
		if (!mapData) return;

		const std::vector<tmx::Layer::Ptr>& layers = mapData->getLayers();
		if (VectorExtensions::IsIndexOutsideBounds(layers, command.layerIndex)) return;

		const tmx::Layer::Ptr& layer = layers[command.layerIndex];
		if (layer->getType() != tmx::Layer::Type::Tile) return;;

		const tmx::TileLayer& tileLayer = layer->getLayerAs<tmx::TileLayer>();

		const std::vector<tmx::TileLayer::Tile>& layerTileIds = tileLayer.getTiles();

		const tmx::Vector2u pixelSizeOfTile = mapData->getTileSize();
		if (pixelSizeOfTile.x == 0 || pixelSizeOfTile.y == 0) return;

		const glm::i32vec2 layerGridSize = command.tiledMapResource->GetGridSize();

		const std::vector<tmx::Tileset>& tileSets = mapData->getTilesets();

		for (std::int32_t y = 0; y < layerGridSize.y; ++y)
		{
			for (std::int32_t x = 0; x < layerGridSize.x; ++x)
			{
				const std::int32_t tileIdIndex = y * layerGridSize.x + x;

				const bool outsideTileIdsBounds = tileIdIndex >= layerTileIds.size();
				if (outsideTileIdsBounds) continue;

				const std::uint32_t tileId = layerTileIds[tileIdIndex].ID;

				const int tileSetIndex = command.tiledMapResource->GetTilesetIndexForTileId(tileId);

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

				const std::shared_ptr<TextureResource> tileSetTexture = command.tiledMapResource->GetTilesetTexture(tileSetIndex).lock();
				if (!tileSetTexture) continue;

				const Texture2D& rawTexture = tileSetTexture->GetRawTexture();

				const tmx::Vector2<int> textureSize = tmx::Vector2(rawTexture.width, rawTexture.height);

				const std::int32_t tileSetGridSizeX = MathExtensions::SafeDivide(
					textureSize.x - (2 * tileSetMargin) + tileSetSpacing,
					pixelSizeOfTile.x + tileSetSpacing
					);

				const std::int32_t idIndex = tileId - tileSet.getFirstGID();
				const float tileNormalizedPositionOnTileSetX = static_cast<float>(idIndex % tileSetGridSizeX);
				const float tileNormalizedPositionOnTileSetY = static_cast<float>(idIndex / tileSetGridSizeX);

				const float tileStartOnTileSetTextureX = tileSetMargin + tileNormalizedPositionOnTileSetX * (pixelSizeOfTile.x + tileSetSpacing);
				const float tileStartOnTileSetTextureY = tileSetMargin + tileNormalizedPositionOnTileSetY * (pixelSizeOfTile.y + tileSetSpacing);

				const glm::i32vec2 girdPosition = command.tiledMapResource->TiledGridPositionToEngineGridPosition({ x, y });

				const glm::vec2 finalPosition = TiledMap2dRendererComponent::GridPositionToWorldPosition(
					layerGridSize,
					{pixelSizeOfTile.x, pixelSizeOfTile.y},
					command.position,
					command.rotationRadians,
					command.scale,
					girdPosition,
					CellPosition::CENTER
					);

				rlRectangle source = {
					tileStartOnTileSetTextureX,
					tileStartOnTileSetTextureY,
					static_cast<float>(pixelSizeOfTile.x),
					static_cast<float>(pixelSizeOfTile.y)
				};

				DrawTexture(
					rawTexture,
					source,
					finalPosition,
					command.rotationRadians,
					command.scale,
					Color01::White
					);
			}
		}
	}
} // GEngineCore
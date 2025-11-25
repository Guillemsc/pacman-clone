//
// Created by guillem on 6/20/25.
//

#include "TiledMapResource.h"

#include <ranges>
#include "glm/vec2.hpp"

#include "GEngine/Extensions/VectorExtensions.h"
#include "tmxlite/TileLayer.hpp"

namespace GEngine
{
	TiledMapResource::TiledMapResource(
		const std::filesystem::path &fullPath,
		const std::filesystem::path &resourcesPath,
		const std::shared_ptr<tmx::Map>& tiledMap,
		const std::map<std::int32_t, std::int32_t>& tilesetFirstGuidByTilesetIndex
		) : Resource(fullPath, resourcesPath)
	{
		_tiledMapPtr = tiledMap;
		_tilesetFirstGuidByTilesetIndex = tilesetFirstGuidByTilesetIndex;
	}

	std::weak_ptr<tmx::Map> TiledMapResource::GetRawMap() const
	{
		return _tiledMapPtr;
	}

	glm::i32vec2 TiledMapResource::GetGridSize() const
	{
		if (!_tiledMapPtr) return {0, 0};

		const tmx::Vector2u gridSize = _tiledMapPtr->getTileCount();

		return { gridSize.x, gridSize.y };
	}

	std::int32_t TiledMapResource::GetLayerIndexFromLayerName(const std::string &layerName) const
	{
		if (!_tiledMapPtr) return -1;

		const std::vector<tmx::Layer::Ptr>& layers = _tiledMapPtr->getLayers();

		for (std::int32_t i = 0; i < layers.size(); ++i)
		{
			if (layers[i]->getName() == layerName)
			{
				return i;
			}
		}

		return -1;
	}

	std::optional<std::reference_wrapper<const tmx::TileLayer>> TiledMapResource::GetTileLayer(const std::int32_t layerIndex) const
	{
		if (!_tiledMapPtr) return std::nullopt;

		const std::vector<tmx::Layer::Ptr>& layers = _tiledMapPtr->getLayers();

		if (VectorExtensions::IsIndexOutsideBounds(layers, layerIndex)) return std::nullopt;

		const tmx::Layer::Ptr& layer = layers[layerIndex];

		if (layer->getType() != tmx::Layer::Type::Tile) return std::nullopt;

		const tmx::TileLayer& tileLayer = layer->getLayerAs<tmx::TileLayer>();

		return std::cref(tileLayer);
	}

	std::int32_t TiledMapResource::GetTileIdFromGridPosition(const tmx::TileLayer& layer, const glm::i32vec2 &gridPosition) const
	{
		if (!_tiledMapPtr) return 0;
		const tmx::Vector2u mapGridSize = _tiledMapPtr->getTileCount();

		const std::int32_t tileIdIndex = gridPosition.y * mapGridSize.x + gridPosition.x;
		const std::vector<tmx::TileLayer::Tile>& tiles = layer.getTiles();

		const bool outsideTileIdsBounds = tileIdIndex >= tiles.size();
		if (outsideTileIdsBounds) return 0;

		return tiles[tileIdIndex].ID;
	}

	glm::i32vec2 TiledMapResource::GetGridPositionFromTileId(const uint32_t gid) const
	{
		if (!_tiledMapPtr) return { 0, 0 };
		const tmx::Vector2u mapGridSize = _tiledMapPtr->getTileCount();

		std::int32_t x = gid % mapGridSize.x;
		std::int32_t y = gid / mapGridSize.x;

		return { x, y };
	}

	std::int32_t TiledMapResource::GetTilesetIndexForTileId(const uint32_t gid) const
	{
		std::int32_t match = 0;

		for (const auto &[fst, snd] : _tilesetFirstGuidByTilesetIndex)
		{
			if (gid >= fst)
			{
				match = snd;
			}
		}

		return match;
	}

	std::optional<std::reference_wrapper<const tmx::Tileset>> TiledMapResource::GetTilesetForTileID(const uint32_t gid) const
	{
		if (!_tiledMapPtr) return std::nullopt;
		const std::vector<tmx::Tileset>& tileSets = _tiledMapPtr->getTilesets();

		const std::int32_t tilesetIndex = GetTilesetIndexForTileId(gid);
		if (VectorExtensions::IsIndexOutsideBounds(tileSets, tilesetIndex)) return std::nullopt;

		const tmx::Tileset& tileSet = tileSets[tilesetIndex];

		return std::cref(tileSet);
	}

	std::weak_ptr<TextureResource> TiledMapResource::GetTilesetTexture(const int index) const
	{
		return VectorExtensions::GetOrDefault(_tileSetTextures, index, std::weak_ptr<TextureResource>());
	}

	std::int32_t TiledMapResource::GetLocalTilesetIndexForTileID(const tmx::Tileset& tileset, const uint32_t gid)
	{
		return  gid - tileset.getFirstGID();
	}

	std::string TiledMapResource::GetTilesetTileStringProperty(
		const tmx::Tileset::Tile *tile,
		const std::string &name,
		const std::string &defaultValue
		)
	{
		for (tmx::Property property : tile->properties)
		{
			if (property.getType() != tmx::Property::Type::String) continue;
			if (property.getName() != name) continue;

			return property.getStringValue();
		}

		return defaultValue;
	}
} // GEngineCore
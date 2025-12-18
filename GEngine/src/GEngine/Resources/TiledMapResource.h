//
// Created by guillem on 6/20/25.
//

#ifndef TILEDMAPRESOURCE_H
#define TILEDMAPRESOURCE_H

#include <optional>

#include "Resource.h"
#include "glm/fwd.hpp"

#include "tmxlite/Map.hpp"

namespace GEngine
{
	class TextureResource;

	class TiledMapResource final : public Resource
	{
		friend class TiledMapResourceImporter;

	public:
		TiledMapResource(
			const std::filesystem::path& fullPath,
			const std::filesystem::path& resourcesPath,
			const std::shared_ptr<tmx::Map>& tiledMap,
			const std::map<std::int32_t, std::int32_t>& tilesetFirstGuidByTilesetIndex
		);

		static ResourceType GetTypeStatic() { return ResourceType::TILED_MAP; }
		ResourceType GetType() override { return GetTypeStatic(); }
		const char* GetTypeName() override { return "Tiled Map"; }

		std::weak_ptr<tmx::Map> GetRawMap() const;

		glm::i32vec2 GetGridSize() const;
		[[nodiscard]] glm::vec2 GetTilePixelSize() const;
		glm::i32vec2 TiledGridPositionToEngineGridPosition(glm::i32vec2 gridPosition) const;

		std::int32_t GetLayerIndexFromLayerName(const std::string& layerName) const;
		std::optional<std::reference_wrapper<const tmx::TileLayer>> GetTileLayer(std::int32_t layerIndex) const;
		std::optional<std::reference_wrapper<const tmx::ObjectGroup>> GetObjectLayer(std::int32_t layerIndex) const;

		std::int32_t GetTileIdFromTiledGridPosition(const tmx::TileLayer& layer, const glm::i32vec2& gridPosition) const;
		std::int32_t GetTilesetIndexForTileId(uint32_t gid) const;
		std::optional<std::reference_wrapper<const tmx::Tileset>> GetTilesetForTileID(uint32_t gid) const;
		std::optional<const tmx::Tileset::Tile*> GetLocalTileForTiledGridPosition(const tmx::TileLayer& tileLayer, const glm::i32vec2& gridPosition) const;

		glm::i32vec2 GetGridPositionFromTiledLocalMapPosition(const glm::vec2& localMapPosition) const;

		std::weak_ptr<TextureResource> GetTilesetTexture(int index) const;

		static std::int32_t GetLocalTilesetIndexForTileID(const tmx::Tileset& tileset, uint32_t gid);
		static std::string GetTilesetTileStringProperty(const tmx::Tileset::Tile* tile, const std::string& name, const std::string& defaultValue);

	protected:
		void Dispose() override;

	private:
		std::shared_ptr<tmx::Map> _tiledMapPtr;
		std::map<std::int32_t, std::int32_t> _tilesetFirstGuidByTilesetIndex;
		std::vector<std::weak_ptr<TextureResource>> _tileSetTextures;
	};
}

#endif //TILEDMAPRESOURCE_H

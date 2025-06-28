//
// Created by guillem on 6/20/25.
//

#ifndef TILEDMAPRESOURCE_H
#define TILEDMAPRESOURCE_H

#include "Resource.h"

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

		std::int32_t GetTileSetIndexForTileID(uint32_t gid) const;
		std::weak_ptr<TextureResource> GetTileSetTexture(int index) const;

	private:
		std::shared_ptr<tmx::Map> _tiledMapPtr;
		std::map<std::int32_t, std::int32_t> _tilesetFirstGuidByTilesetIndex;
		std::vector<std::weak_ptr<TextureResource>> _tileSetTextures;
	};
}

#endif //TILEDMAPRESOURCE_H

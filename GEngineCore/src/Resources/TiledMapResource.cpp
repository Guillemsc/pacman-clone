//
// Created by guillem on 6/20/25.
//

#include "TiledMapResource.h"

#include <ranges>

namespace GEngineCore
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

	std::int32_t TiledMapResource::GetTilesetIndexForTileID(const uint32_t gid) const
	{
		std::int32_t match = 0;

		for (const auto &[fst, snd]: _tilesetFirstGuidByTilesetIndex)
		{
			if (gid >= fst)
			{
				match = snd;
			}
		}

		return match;
	}
} // GEngineCore
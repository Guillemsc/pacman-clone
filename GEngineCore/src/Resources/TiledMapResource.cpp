//
// Created by guillem on 6/20/25.
//

#include "TiledMapResource.h"

namespace GEngineCore
{
	TiledMapResource::TiledMapResource(
		const std::filesystem::path &fullPath,
		const std::filesystem::path &resourcesPath,
		const std::shared_ptr<tmx::Map>& tiledMap
		) : Resource(fullPath, resourcesPath)
	{
		_tiledMapPtr = tiledMap;
	}

	std::weak_ptr<tmx::Map> TiledMapResource::GetRawMap() const
	{
		return _tiledMapPtr;
	}
} // GEngineCore
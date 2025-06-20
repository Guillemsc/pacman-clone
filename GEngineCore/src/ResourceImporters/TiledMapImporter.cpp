//
// Created by guillem on 6/20/25.
//

#include "TiledMapImporter.h"

#include "Resources/TiledMapResource.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/Tileset.hpp"

namespace GEngineCore
{
	TiledMapImporter::TiledMapImporter()
	{
		AddSupportedExtension(".tmx");
	}

	std::shared_ptr<Resource> TiledMapImporter::Import(
		const std::filesystem::path &fullPath,
		const std::filesystem::path &resourcesPath
		)
	{
		const std::shared_ptr<tmx::Map> tiledMap = std::make_shared<tmx::Map>();

		const bool couldLoad = tiledMap->load(fullPath);

		if (!couldLoad)
		{
			return nullptr;
		}

		std::shared_ptr<TiledMapResource> resource = std::make_shared<TiledMapResource>(
			fullPath,
			resourcesPath,
			tiledMap
			);

		return resource;
	}
} // GEngineCore
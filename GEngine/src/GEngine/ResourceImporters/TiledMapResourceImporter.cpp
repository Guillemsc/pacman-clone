//
// Created by guillem on 6/20/25.
//

#include "TiledMapResourceImporter.h"

#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Resources/TextureResource.h"
#include "GEngine/Resources/TiledMapResource.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include "tmxlite/Tileset.hpp"
#include "glm/vec2.hpp"

namespace GEngine
{
	TiledMapResourceImporter::TiledMapResourceImporter(GEngineCoreModules* modules)
		: ResourceImporter(modules)
	{
		AddSupportedExtension(".tmx");
	}

	std::shared_ptr<Resource> TiledMapResourceImporter::Import(
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

		std::map<std::int32_t, std::int32_t> tilesetFirstGuidByTilesetIndex;

		const std::vector<tmx::Tileset>& tileSets = tiledMap->getTilesets();

		for (int i = 0; i < tileSets.size(); ++i)
		{
			const tmx::Tileset& tileSet = tileSets[i];

			tilesetFirstGuidByTilesetIndex.emplace(tileSet.getFirstGID(), i);
		}

		std::shared_ptr<TiledMapResource> resource = std::make_shared<TiledMapResource>(
			fullPath,
			resourcesPath,
			tiledMap,
			tilesetFirstGuidByTilesetIndex
			);

		return resource;
	}

	void TiledMapResourceImporter::AfterImport(const Resource *resource)
	{
		TiledMapResource* tiledMapResource = (TiledMapResource*)resource;

		const std::shared_ptr<tmx::Map> mapData = tiledMapResource->GetRawMap().lock();
		if (!mapData) return;

		const std::vector<tmx::Tileset>& tileSets = mapData->getTilesets();

		for (int i = 0; i < tileSets.size(); ++i)
		{
			const tmx::Tileset& tileSet = tileSets[i];

			const std::string& imagePath = tileSet.getImagePath();
			std::string resourcesImagePath = _modules->resources->FullPathToRelativeResourcesPath(imagePath);
			const std::weak_ptr<TextureResource> tilesetTexture = _modules->resources->GetResource<TextureResource>(resourcesImagePath);

			tiledMapResource->_tileSetTextures.push_back(tilesetTexture);
		}
	}
} // GEngineCore
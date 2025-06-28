//
// Created by guillem on 6/20/25.
//

#include "TiledMapResourceImporter.h"

#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Resources/TextureResource.h"
#include "GEngine/Resources/TiledMapResource.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/Tileset.hpp"

namespace GEngine
{
	TiledMapResourceImporter::TiledMapResourceImporter(const std::weak_ptr<GEngineCoreApplication> &app)
		: ResourceImporter(app)
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
		const std::shared_ptr<GEngineCoreApplication> app = _app.lock();
		if (app == nullptr) return;

		const std::shared_ptr<ResourcesModule> resources = app->Resources().lock();
		if (resources == nullptr) return;

		TiledMapResource* tiledMapResource = (TiledMapResource*)resource;

		const std::shared_ptr<tmx::Map> mapData = tiledMapResource->GetRawMap().lock();
		if (!mapData) return;

		const std::vector<tmx::Tileset>& tileSets = mapData->getTilesets();

		for (int i = 0; i < tileSets.size(); ++i)
		{
			const tmx::Tileset& tileSet = tileSets[i];

			const std::string& imagePath = tileSet.getImagePath();
			std::string resourcesImagePath = resources->FullPathToRelativeResourcesPath(imagePath);
			const std::weak_ptr<TextureResource> tilesetTexture = resources->GetResource<TextureResource>(resourcesImagePath);

			tiledMapResource->_tileSetTextures.push_back(tilesetTexture);
		}
	}
} // GEngineCore
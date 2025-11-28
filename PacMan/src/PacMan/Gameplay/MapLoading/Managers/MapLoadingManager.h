//
// Created by guillem on 11/25/25.
//

#ifndef MAPLOADINGMANAGER_H
#define MAPLOADINGMANAGER_H

#include <string>

#include "GEngine/Resources/TiledMapResource.h"
#include "GEngine/Scenes/Scene.h"
#include "glm/fwd.hpp"
#include "PacMan/Gameplay/MapLoading/Data/LoadedMapData.h"
#include "tmxlite/Tileset.hpp"

namespace GEngine
{
	class GEngineCoreModules;
}

namespace PacMan
{
	struct LoadedMapData;

	class MapLoadingManager
	{
	public:
		explicit MapLoadingManager(GEngine::GEngineCoreModules* modules, GEngine::Scene* scene);

		void LoadMap(const std::string& mapFileName);
		const LoadedMapData& GetLoadedMapData() const;

	private:
		void LoadTilemapGameObject(
			LoadedMapData& loadedMapData,
			const std::shared_ptr<GEngine::TiledMapResource>& tilemapResource
		);

		void LoadMapEntities(
			LoadedMapData& loadedMapData,
			const std::shared_ptr<GEngine::TiledMapResource>& tilemapResource
			);

		void LoadTileData(LoadedMapData& loadedMapData, const glm::i32vec2& gridPosition, const tmx::Tileset::Tile *localTile);

	private:
		GEngine::GEngineCoreModules* const _modules;
		GEngine::Scene* const _scene;

		LoadedMapData _loadedMapData;
	};
}

#endif //MAPLOADINGMANAGER_H

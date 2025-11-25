//
// Created by guillem on 11/25/25.
//

#ifndef MAPLOADINGMANAGER_H
#define MAPLOADINGMANAGER_H

#include <string>

#include "glm/fwd.hpp"
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
		explicit MapLoadingManager(GEngine::GEngineCoreModules* modules);

		void LoadMap(const std::string& mapFileName);

	private:
		void LoadTileData(LoadedMapData& loadedMapData, const glm::i32vec2& gridPosition, const tmx::Tileset::Tile *localTile);

	private:
		GEngine::GEngineCoreModules* const _modules;
	};
}

#endif //MAPLOADINGMANAGER_H

//
// Created by guillem on 11/25/25.
//

#include "MapLoadingManager.h"

#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Resources/TiledMapResource.h"
#include "PacMan/Gameplay/MapLoading/Data/LoadedMapData.h"
#include "spdlog/spdlog.h"
#include "tmxlite/TileLayer.hpp"

namespace PacMan
{
	MapLoadingManager::MapLoadingManager(GEngine::GEngineCoreModules *modules) : _modules(modules)
	{
	}

	void MapLoadingManager::LoadMap(const std::string &mapFileName)
	{
		const std::string entitiesLayer = "Entities";
		const std::filesystem::path mapsBasePath = "Tiled/maps";

		LoadedMapData loadedMapData;

		const std::filesystem::path mapPath = mapsBasePath / (mapFileName + ".tmx");

		const std::shared_ptr<GEngine::TiledMapResource> tilemapResource
			= _modules->resources->GetResource<GEngine::TiledMapResource>(mapPath).lock();
		if (!tilemapResource) return;

		const std::int32_t entitiesLayerIndex = tilemapResource->GetLayerIndexFromLayerName(entitiesLayer);
		if (entitiesLayerIndex < 0) return;

		const auto optionalLayer = tilemapResource->GetTileLayer(entitiesLayerIndex);
		if (!optionalLayer) return;
		const tmx::TileLayer& tileLayer = optionalLayer->get();

		const glm::i32vec2 gridSize = tilemapResource->GetGridSize();

		for (std::int32_t y = 0; y < gridSize.y; ++y)
		{
			for (std::int32_t x = 0; x < gridSize.x; ++x)
			{
				const glm::i32vec2 gridPosition = { x, y };
				std::int32_t tileId = tilemapResource->GetTileIdFromGridPosition(tileLayer, gridPosition);
				if (tileId == 0) continue;

				auto optionalTileset = tilemapResource->GetTilesetForTileID(tileId);
				if (!optionalTileset.has_value()) continue;
				const tmx::Tileset& tileset = optionalTileset.value();

				const tmx::Tileset::Tile* localTile = tileset.getTile(tileId);
				if (localTile == nullptr) continue;

				LoadTileData(loadedMapData, gridPosition, localTile);
			}
		}

		spdlog::info("Map data loaded [Player:x{0} y{1}] [RedGhost:x{2} y{3}]",
			loadedMapData.PlayerPosition.x,
			loadedMapData.PlayerPosition.y,
			loadedMapData.RedGhostPosition.x,
			loadedMapData.RedGhostPosition.y
			);
	}

	void MapLoadingManager::LoadTileData(LoadedMapData& loadedMapData, const glm::i32vec2& gridPosition, const tmx::Tileset::Tile *localTile)
	{
		const std::string typeProperty = GEngine::TiledMapResource::GetTilesetTileStringProperty(localTile, "type", "");

		if (typeProperty == "player")
		{
			loadedMapData.PlayerPosition = gridPosition;
		}

		if (typeProperty == "redGhost")
		{
			loadedMapData.RedGhostPosition = gridPosition;
		}

		if (typeProperty == "cianGhost")
		{
			loadedMapData.CianGhostPosition = gridPosition;
		}

		if (typeProperty == "pinkGhost")
		{
			loadedMapData.PinkGhostPosition = gridPosition;
		}

		if (typeProperty == "orangeGhost")
		{
			loadedMapData.OrangeGhostPosition = gridPosition;
		}
	}
} // PacMan
//
// Created by guillem on 11/25/25.
//

#include "MapLoadingManager.h"

#include "GEngine/Components/TiledMap2dRendererComponent.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Resources/TiledMapResource.h"
#include "PacMan/Gameplay/MapLoading/Data/LoadedMapData.h"
#include "spdlog/spdlog.h"
#include "tmxlite/TileLayer.hpp"

namespace PacMan
{
	MapLoadingManager::MapLoadingManager(GEngine::GEngineCoreModules *modules, GEngine::Scene* scene)
		: _modules(modules), _scene(scene)
	{
	}

	void MapLoadingManager::LoadMap(const std::string &mapFileName)
	{
		const std::filesystem::path mapsBasePath = "Tiled/maps";

		const std::filesystem::path mapPath = mapsBasePath / (mapFileName + ".tmx");

		const std::shared_ptr<GEngine::TiledMapResource> tilemapResource
			= _modules->resources->GetResource<GEngine::TiledMapResource>(mapPath).lock();
		if (!tilemapResource) return;

		LoadTilemapGameObject(_loadedMapData, tilemapResource);
		LoadMapEntities(_loadedMapData, tilemapResource);

		spdlog::info("Map data loaded [Player:x{0} y{1}] [RedGhost:x{2} y{3}] [CianGhost:x{4} y{5}] [PinkGhost:x{6} y{7}] [OrangeGhost:x{8} y{9}]",
			_loadedMapData.PlayerPosition.x,
			_loadedMapData.PlayerPosition.y,
			_loadedMapData.RedGhostPosition.x,
			_loadedMapData.RedGhostPosition.y,
			_loadedMapData.GhostPrision1Position.x,
			_loadedMapData.GhostPrision1Position.y,
			_loadedMapData.GhostPrision2Position.x,
			_loadedMapData.GhostPrision2Position.y,
			_loadedMapData.GhostPrision3Position.x,
			_loadedMapData.GhostPrision3Position.y
			);
	}

	const LoadedMapData & MapLoadingManager::GetLoadedMapData() const
	{
		return _loadedMapData;
	}

	void MapLoadingManager::LoadTilemapGameObject(LoadedMapData& loadedMapData, const std::shared_ptr<GEngine::TiledMapResource> &tilemapResource)
	{
		const std::shared_ptr<GEngine::Entity> tilemapEntity = _scene->AddWorldEntity().lock();
		tilemapEntity->SetName("Tilemap");
		const std::shared_ptr<GEngine::TiledMap2dRendererComponent> tilemap = tilemapEntity->AddComponent<GEngine::TiledMap2dRendererComponent>().lock();

		tilemap->SetTiledMap(tilemapResource);

		loadedMapData.Tilemap = tilemap;
	}

	void MapLoadingManager::LoadMapEntities(
		LoadedMapData& loadedMapData,
		const std::shared_ptr<GEngine::TiledMapResource>& tilemapResource
	)
	{
		const std::string entitiesLayer = "Entities";

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
				const std::int32_t tileId = tilemapResource->GetTileIdFromGridPosition(tileLayer, gridPosition);
				if (tileId == 0) continue;

				auto optionalTileset = tilemapResource->GetTilesetForTileID(tileId);
				if (!optionalTileset.has_value()) continue;
				const tmx::Tileset& tileset = optionalTileset.value();

				const tmx::Tileset::Tile* localTile = tileset.getTile(tileId);
				if (localTile == nullptr) continue;

				LoadTileData(loadedMapData, gridPosition, localTile);
			}
		}
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

		if (typeProperty == "ghostPrision1")
		{
			loadedMapData.GhostPrision1Position = gridPosition;
		}

		if (typeProperty == "ghostPrision2")
		{
			loadedMapData.GhostPrision2Position = gridPosition;
		}

		if (typeProperty == "ghostPrision3")
		{
			loadedMapData.GhostPrision3Position = gridPosition;
		}
	}
} // PacMan
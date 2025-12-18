//
// Created by guillem on 11/25/25.
//

#include "MapLoadingManager.h"

#include "GEngine/Components/TiledMap2dRendererComponent.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Logging/GEngineLog.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Resources/TiledMapResource.h"
#include "PacMan/Gameplay/Layers/Enums/RenderingLayer.h"
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
		GGAME_INFO("Starting map loading.");

		const std::filesystem::path mapsBasePath = "Tiled/maps";

		const std::filesystem::path mapPath = mapsBasePath / (mapFileName + ".tmx");
		const std::string mapPathString = mapPath.string();

		const std::shared_ptr<GEngine::TiledMapResource> tilemapResource
			= _modules->resources->GetResource<GEngine::TiledMapResource>(mapPathString).lock();

		if (!tilemapResource)
		{
			GCLIENT_ERROR("Failed to load map {}.", mapPathString);
			return;
		}

		LoadTilemapGameObject(_loadedMapData, tilemapResource);
		LoadTilesMapData(_loadedMapData, tilemapResource.get());
		LoadPortalsMapData(_loadedMapData, tilemapResource.get());

		GGAME_INFO("Map data loaded [Player:x{0} y{1}] [RedGhost:x{2} y{3}] [CianGhost:x{4} y{5}] [PinkGhost:x{6} y{7}] [OrangeGhost:x{8} y{9}].",
			_loadedMapData.PlayerPosition.x,
			_loadedMapData.PlayerPosition.y,
			_loadedMapData.MapGhostPosition.x,
			_loadedMapData.MapGhostPosition.y,
			_loadedMapData.GhostPrisionLeftSlotGridPosition.x,
			_loadedMapData.GhostPrisionLeftSlotGridPosition.y,
			_loadedMapData.GhostPrisionCenterSlotGridPosition.x,
			_loadedMapData.GhostPrisionCenterSlotGridPosition.y,
			_loadedMapData.GhostPrisionRightSlotGridPosition.x,
			_loadedMapData.GhostPrisionRightSlotGridPosition.y
			);
	}

	const LoadedMapData & MapLoadingManager::GetLoadedMapData() const
	{
		return _loadedMapData;
	}

	void MapLoadingManager::LoadTilemapGameObject(
		LoadedMapData& loadedMapData,
		const std::shared_ptr<GEngine::TiledMapResource> &tilemapResource
		) const
	{
		const std::shared_ptr<GEngine::Entity> tilemapEntity = _scene->AddWorldEntity().lock();
		tilemapEntity->SetName("Tilemap");

		const std::shared_ptr<GEngine::TiledMap2dRendererComponent> tilemap = tilemapEntity->AddComponent<GEngine::TiledMap2dRendererComponent>().lock();
		tilemap->SetRenderLayer(static_cast<std::int32_t>(RenderingLayer::MAP));
		tilemap->SetTiledMap(tilemapResource);

		const std::int32_t hiddingTileLayer = tilemap->GetTileLayerIndexFromName("HiddingPlane");
		tilemap->SetTileLayerRenderLayerOffset(hiddingTileLayer, static_cast<std::int32_t>(RenderingLayer::MAP_HIDDING_PLANE));

		loadedMapData.Tilemap = tilemap;
		loadedMapData.MapBounds = tilemap->GetWorldBounds();
	}

	void MapLoadingManager::LoadTilesMapData(
		LoadedMapData& loadedMapData,
		GEngine::TiledMapResource* tilemapResource
	)
	{
		const std::string entitiesLayer = "Entities";
		const std::string walkabilityLayer = "Walkability";
		const std::string pelletsLayer = "Pellets";
		const std::string portalsLayer = "Portals";

		const glm::i32vec2 gridSize = tilemapResource->GetGridSize();

		const std::int32_t entitiesLayerIndex = tilemapResource->GetLayerIndexFromLayerName(entitiesLayer);
		if (entitiesLayerIndex < 0) return;

		const std::int32_t walkabilityLayerIndex = tilemapResource->GetLayerIndexFromLayerName(walkabilityLayer);
		if (walkabilityLayerIndex < 0) return;

		const std::int32_t pelletsLayerIndex = tilemapResource->GetLayerIndexFromLayerName(pelletsLayer);
		if (pelletsLayerIndex < 0) return;

		const auto optionalEntitiesLayer = tilemapResource->GetTileLayer(entitiesLayerIndex);
		if (!optionalEntitiesLayer) return;
		const tmx::TileLayer& entitiesTileLayer = optionalEntitiesLayer->get();

		const auto optionalWalkabilityLayer = tilemapResource->GetTileLayer(walkabilityLayerIndex);
		if (!optionalWalkabilityLayer) return;
		const tmx::TileLayer& walkabilityTileLayer = optionalWalkabilityLayer->get();

		const auto optionalPelletsLayer = tilemapResource->GetTileLayer(pelletsLayerIndex);
		if (!optionalPelletsLayer) return;
		const tmx::TileLayer& pelletsTileLayer = optionalPelletsLayer->get();

		for (std::int32_t y = 0; y < gridSize.y; ++y)
		{
			for (std::int32_t x = 0; x < gridSize.x; ++x)
			{
				const glm::i32vec2 gridPosition = { x, y };

				auto optionalEntityLocalTile = tilemapResource->GetLocalTileForTiledGridPosition(entitiesTileLayer, gridPosition);

				if (optionalEntityLocalTile.has_value())
				{
					const tmx::Tileset::Tile* localTile = optionalEntityLocalTile.value();
					LoadEntityTileData(loadedMapData, gridPosition, localTile);
				}

				auto optionalWalkabilityLocalTile = tilemapResource->GetLocalTileForTiledGridPosition(walkabilityTileLayer, gridPosition);

				if (optionalWalkabilityLocalTile.has_value())
				{
					const tmx::Tileset::Tile* walkabilityLocalTile = optionalWalkabilityLocalTile.value();
					LoadWalkabilityTileData(loadedMapData, gridPosition, walkabilityLocalTile);
				}

				auto optionalPelletsLocalTile = tilemapResource->GetLocalTileForTiledGridPosition(pelletsTileLayer, gridPosition);

				if (optionalPelletsLocalTile.has_value())
				{
					const tmx::Tileset::Tile* pelletLocalTile = optionalPelletsLocalTile.value();
					LoadPelletsTileData(loadedMapData, gridPosition, pelletLocalTile);
				}
			}
		}
	}

	void MapLoadingManager::LoadPortalsMapData(
		LoadedMapData &loadedMapData,
		const GEngine::TiledMapResource* tilemapResource
		)
	{
		const std::string portalsLayer = "Portals";

		const std::int32_t portalsLayerIndex = tilemapResource->GetLayerIndexFromLayerName(portalsLayer);
		if (portalsLayerIndex < 0) return;

		const auto optionalPortalsLayer = tilemapResource->GetObjectLayer(portalsLayerIndex);
		if (!optionalPortalsLayer) return;
		const tmx::ObjectGroup& portalsTileLayer = optionalPortalsLayer->get();

		const std::vector<tmx::Object>& portalObjects = portalsTileLayer.getObjects();

		for (int i = 0; i < portalObjects.size(); ++i)
		{
			const tmx::Object& object = portalObjects[i];

			int r = 2;
		}
	}

	void MapLoadingManager::LoadEntityTileData(
		LoadedMapData& loadedMapData,
		const glm::i32vec2& gridPosition,
		const tmx::Tileset::Tile *localTile
		)
	{
		const std::string typeProperty = GEngine::TiledMapResource::GetTilesetTileStringProperty(localTile, "type", "");

		if (typeProperty == "player")
		{
			loadedMapData.PlayerPosition = gridPosition;
		}

		if (typeProperty == "redGhost")
		{
			loadedMapData.MapGhostPosition = gridPosition;
		}

		if (typeProperty == "ghostPrision1")
		{
			loadedMapData.GhostPrisionLeftSlotGridPosition = gridPosition;
		}

		if (typeProperty == "ghostPrision2")
		{
			loadedMapData.GhostPrisionCenterSlotGridPosition = gridPosition;
		}

		if (typeProperty == "ghostPrision3")
		{
			loadedMapData.GhostPrisionRightSlotGridPosition = gridPosition;
		}
	}

	void MapLoadingManager::LoadWalkabilityTileData(
		LoadedMapData &loadedMapData,
		const glm::i32vec2 &gridPosition,
		const tmx::Tileset::Tile *localTile
		)
	{
		const std::string typeProperty = GEngine::TiledMapResource::GetTilesetTileStringProperty(localTile, "type", "");

		if (typeProperty == "prision_exit")
		{
			loadedMapData.PrisionExitPosition = gridPosition;
		}
	}

	void MapLoadingManager::LoadPelletsTileData(
		LoadedMapData &loadedMapData,
		const glm::i32vec2 &gridPosition,
		const tmx::Tileset::Tile *localTile
		)
	{
		const std::string typeProperty = GEngine::TiledMapResource::GetTilesetTileStringProperty(localTile, "type", "");

		if (typeProperty == "big")
		{
			loadedMapData.BigPelletsPositions.push_back(gridPosition);
		}
		else
		{
			loadedMapData.SmallPelletsPositions.push_back(gridPosition);
		}
	}
} // PacMan
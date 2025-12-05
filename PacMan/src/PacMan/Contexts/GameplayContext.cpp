//
// Created by guillem on 6/30/25.
//

#include "GameplayContext.h"

#include "GEngine/Components/Shape2dRendererComponent.h"
#include "GEngine/Components/TiledMap2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Modules/EntitiesModule.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Modules/TickablesModule.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "GEngine/Resources/TiledMapResource.h"
#include "PacMan/Gameplay/Entities/Managers/EntitiesManager.h"
#include "PacMan/Gameplay/Ghosts/Managers/GhostsLoadingManager.h"
#include "PacMan/Gameplay/Ghosts/Managers/GhostsPrisionManager.h"
#include "PacMan/Gameplay/Input/Systems/PlayerInputSystem.h"
#include "PacMan/Gameplay/MapLoading/Managers/MapLoadingManager.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"
#include "PacMan/Gameplay/Player/Managers/PlayerLoaderManager.h"
#include "PacMan/Gameplay/Ghosts/Managers/GhostsPrisionManager.h"
#include "PacMan/Gameplay/Ghosts/Data/LoadedGhostsData.h"
#include "PacMan/Gameplay/Ghosts/Data/GhostPrisionSlotData.h"

namespace PacMan
{
	GameplayContext::GameplayContext(GEngine::GEngineCoreModules* modules) : Context(modules, "Gameplay")
	{
	}

	tokoro::Async<void> GameplayContext::OnLoadAsync()
	{
		std::unique_ptr<MapLoadingManager> mapLoadingManager = std::make_unique<MapLoadingManager>(
			_modules,
			_scene.get()
			);

		std::unique_ptr<MapMovementManager> mapMovementManager = std::make_unique<MapMovementManager>();
		GEngine::ServiceLocator::Register(mapMovementManager.get());

		std::unique_ptr<GameplayEntities> gameplayEntities = std::make_unique<GameplayEntities>();
		GEngine::ServiceLocator::Register(gameplayEntities.get());

		std::unique_ptr<EntitiesManager> entitiesManager = std::make_unique<EntitiesManager>(
			gameplayEntities.get()
			);

		std::shared_ptr<GhostsPrisionManager> ghostsPrisionManager = std::make_shared<GhostsPrisionManager>(
			_modules,
			GetCoroutinesRunner(),
			mapMovementManager.get()
			);
		_modules->tickables->AddTickable(ghostsPrisionManager);

		std::shared_ptr<PlayerInputSystem> playerInputSystem = std::make_shared<PlayerInputSystem>();
		_modules->tickables->AddTickable(playerInputSystem);

		std::unique_ptr<PlayerCollisionsManager> playerCollisionsManager = std::make_unique<PlayerCollisionsManager>();

		std::unique_ptr<PlayerLoaderManager> playerLoaderManager = std::make_unique<PlayerLoaderManager>(
			_modules,
			_scene.get(),
			mapMovementManager.get(),
			playerInputSystem.get(),
			gameplayEntities.get(),
			playerCollisionsManager.get()
			);

		std::unique_ptr<PlayerDeathManager> playerDeathManager = std::make_unique<PlayerDeathManager>(
			GetCoroutinesRunner(),
			entitiesManager.get(),
			ghostsPrisionManager.get(),
			playerLoaderManager.get()
			);

		std::unique_ptr<MapPathfindingManager> mapPathfindingManager = std::make_unique<MapPathfindingManager>(mapMovementManager.get());
		GEngine::ServiceLocator::Register(mapPathfindingManager.get());

		std::unique_ptr<GhostsLoadingManager> ghostsLoaderManager = std::make_unique<GhostsLoadingManager>(
			_modules,
			_scene.get(),
			mapMovementManager.get(),
			gameplayEntities.get()
			);

		std::unique_ptr<PelletsLoadingManager> pelletsLoadingManager = std::make_unique<PelletsLoadingManager>(
			_modules,
			_scene.get(),
			mapMovementManager.get()
			);

		playerCollisionsManager->Init(playerDeathManager.get());

		_mapLoadingManager = std::move(mapLoadingManager);
		_mapMovementManager = std::move(mapMovementManager);
		_mapPathfindingManager = std::move(mapPathfindingManager);
		_gameplayEntities = std::move(gameplayEntities);
		_entitiesManager = std::move(entitiesManager);
		_playerLoaderManager = std::move(playerLoaderManager);
		_playerCollisionsManager = std::move(playerCollisionsManager);
		_playerDeathManager = std::move(playerDeathManager);
		_ghostsLoaderManager = std::move(ghostsLoaderManager);
		_ghostsPrisionManager = ghostsPrisionManager;
		_pelletsLoadingManager = std::move(pelletsLoadingManager);
		_playerInputSystem = playerInputSystem;

		_mapLoadingManager->LoadMap("test-map");
		const LoadedMapData loadedMapData = _mapLoadingManager->GetLoadedMapData();

		_mapMovementManager->Setup(loadedMapData.Tilemap);

		_playerLoaderManager->LoadPlayer(loadedMapData.PlayerPosition);

		_ghostsLoaderManager->LoadGhosts(loadedMapData);
		const LoadedGhostsData loadedGhostsData = _ghostsLoaderManager->GetLoadedGhostsData();
		_ghostsPrisionManager->Setup(loadedMapData, loadedGhostsData);

		_pelletsLoadingManager->LoadPellets(loadedMapData);

		co_return;
	}

	void GameplayContext::OnDispose()
	{
		GEngine::ServiceLocator::Unregister<MapMovementManager>();
		GEngine::ServiceLocator::Unregister<GameplayEntities>();
		GEngine::ServiceLocator::Unregister<PlayerDeathManager>();

		_modules->tickables->RemoveTickable(_playerInputSystem);
		_modules->tickables->RemoveTickable(_ghostsPrisionManager);
	}
} // PacMan
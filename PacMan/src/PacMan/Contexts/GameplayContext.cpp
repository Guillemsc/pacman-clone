//
// Created by guillem on 6/30/25.
//

#include "GameplayContext.h"

#include "GEngine/Components/Shape2dRendererComponent.h"
#include "GEngine/Components/TiledMap2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Coroutines/CoroutinesRunner.h"
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
#include "PacMan/Shared/Camera/Data/CameraData.h"

namespace PacMan
{
	GameplayContext::GameplayContext(GEngine::GEngineCoreModules* modules) : Context(modules, "Gameplay")
	{
	}

	tokoro::Async<void> GameplayContext::OnLoadAsync()
	{
		CameraData* cameraData = GEngine::ServiceLocator::Get<CameraData>();

		std::unique_ptr<HudManager> hudManager = std::make_unique<HudManager>(_modules, _scene.get());

		_cameraManager = std::make_shared<CameraManager>(
			cameraData
			);
		_modules->tickables->AddTickable(_cameraManager);

		std::unique_ptr<MapLoadingManager> mapLoadingManager = std::make_unique<MapLoadingManager>(
			_modules,
			_scene.get()
			);

		std::unique_ptr<MapMovementManager> mapMovementManager = std::make_unique<MapMovementManager>();

		std::unique_ptr<GameplayEntities> gameplayEntities = std::make_unique<GameplayEntities>();
		std::unique_ptr<GhostsStateData> ghostsStateData = std::make_unique<GhostsStateData>();

		std::unique_ptr<EntitiesManager> entitiesManager = std::make_unique<EntitiesManager>(
			gameplayEntities.get()
			);

		const std::shared_ptr<GhostsPrisionManager> ghostsPrisionManager = std::make_shared<GhostsPrisionManager>(
			_modules,
			GetCoroutinesRunner(),
			mapMovementManager.get(),
			ghostsStateData.get()
			);
		_modules->tickables->AddTickable(ghostsPrisionManager);

		const std::shared_ptr<PlayerInputSystem> playerInputSystem = std::make_shared<PlayerInputSystem>();
		_modules->tickables->AddTickable(playerInputSystem);

		const std::shared_ptr<GhostsBehaviourManager> ghostsBehaviourManager = std::make_shared<GhostsBehaviourManager>(
			ghostsStateData.get(),
			gameplayEntities.get()
			);
		_modules->tickables->AddTickable(ghostsBehaviourManager);

		std::unique_ptr<PelletCollectionManager> pelletsCollectionManager = std::make_unique<PelletCollectionManager>(
			ghostsBehaviourManager.get()
			);

		std::unique_ptr<PlayerCollisionsManager> playerCollisionsManager = std::make_unique<PlayerCollisionsManager>(
			pelletsCollectionManager.get(),
			ghostsPrisionManager.get(),
			ghostsStateData.get()
			);

		std::unique_ptr<MapPathfindingManager> mapPathfindingManager = std::make_unique<MapPathfindingManager>(mapMovementManager.get());

		std::unique_ptr<PlayerLoaderManager> playerLoaderManager = std::make_unique<PlayerLoaderManager>(
			_modules,
			_scene.get(),
			mapMovementManager.get(),
			playerInputSystem.get(),
			gameplayEntities.get(),
			playerCollisionsManager.get(),
			mapPathfindingManager.get()
			);

		std::unique_ptr<GhostsLoadingManager> ghostsLoaderManager = std::make_unique<GhostsLoadingManager>(
			_modules,
			_scene.get(),
			mapMovementManager.get(),
			mapPathfindingManager.get(),
			gameplayEntities.get(),
			ghostsStateData.get()
			);

		std::unique_ptr<PlayerDeathManager> playerDeathManager = std::make_unique<PlayerDeathManager>(
			GetCoroutinesRunner(),
			entitiesManager.get(),
			ghostsPrisionManager.get(),
			playerLoaderManager.get(),
			ghostsLoaderManager.get(),
			ghostsBehaviourManager.get()
			);

		std::unique_ptr<PelletsLoadingManager> pelletsLoadingManager = std::make_unique<PelletsLoadingManager>(
			_modules,
			_scene.get(),
			mapMovementManager.get()
			);

		playerCollisionsManager->Init(playerDeathManager.get());

		_hudManager = std::move(hudManager);
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
		_ghostsBehaviourManager = ghostsBehaviourManager;
		_ghostsStateData = std::move(ghostsStateData);
		_pelletsLoadingManager = std::move(pelletsLoadingManager);
		_pelletCollectionManager = std::move(pelletsCollectionManager);
		_playerInputSystem = playerInputSystem;

		_mapLoadingManager->LoadMap("test-map");
		const LoadedMapData loadedMapData = _mapLoadingManager->GetLoadedMapData();

		_cameraManager->SetBounds(loadedMapData.MapBounds);
		_mapMovementManager->Setup(loadedMapData.Tilemap, loadedMapData.MapPortals);

		_playerLoaderManager->LoadPlayer(loadedMapData.PlayerPosition);

		_ghostsLoaderManager->LoadGhosts(loadedMapData);
		const LoadedGhostsData loadedGhostsData = _ghostsLoaderManager->GetLoadedGhostsData();
		_ghostsPrisionManager->Setup(loadedMapData, loadedGhostsData);

		_pelletsLoadingManager->LoadPellets(loadedMapData);

		co_return;
	}

	void GameplayContext::OnStart()
	{
		GetCoroutinesRunner()->Start(&GameplayContext::StartGameAsync, this, GEngine::CancellationToken::None()).Forget();
	}

	void GameplayContext::OnDispose()
	{
		_modules->tickables->RemoveTickable(_cameraManager);
		_modules->tickables->RemoveTickable(_playerInputSystem);
		_modules->tickables->RemoveTickable(_ghostsPrisionManager);
		_modules->tickables->RemoveTickable(_ghostsBehaviourManager);
	}

	tokoro::Async<void> GameplayContext::StartGameAsync(const GEngine::CancellationToken cancellationToken)
	{
		co_await _hudManager->ShowAsync(cancellationToken);

		co_await GEngine::ChronoTimer::AwaitSeconds(2, cancellationToken);

		_ghostsBehaviourManager->StartGhostsBehaviours();
		_ghostsPrisionManager->Reset();
		_entitiesManager->StartPlayerAndMapGhostEntitiesMovement();

		co_return;
	}
} // PacMan
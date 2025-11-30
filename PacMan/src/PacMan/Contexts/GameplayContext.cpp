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
#include "GEngine/Modules/SystemsModule.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "GEngine/Resources/TiledMapResource.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"
#include "PacMan/Gameplay/Ghosts/Managers/GhostsLoaderManager.h"
#include "PacMan/Gameplay/Ghosts/Managers/GhostsPrisionManager.h"
#include "PacMan/Gameplay/Input/Systems/PlayerInputSystem.h"
#include "PacMan/Gameplay/MapLoading/Managers/MapLoadingManager.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapPathfindingManager.h"
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
		const std::shared_ptr<MapLoadingManager> mapLoadingManager = std::make_shared<MapLoadingManager>(_modules, _scene.get());
		mapLoadingManager->LoadMap("test-map");
		const LoadedMapData loadedMapData = mapLoadingManager->GetLoadedMapData();

		_mapMovementManager = std::make_shared<MapMovementManager>(loadedMapData.Tilemap);
		GEngine::ServiceLocator::Register(_mapMovementManager);

		_mapPathfindingManager = std::make_shared<MapPathfindingManager>(_mapMovementManager.get());
		GEngine::ServiceLocator::Register(_mapPathfindingManager);

		_playerInputSystem = std::make_shared<PlayerInputSystem>();
		_modules->systems->AddSystem(_playerInputSystem);

		_gameplayEntities = std::make_shared<GameplayEntities>();
		GEngine::ServiceLocator::Register(_gameplayEntities);

		_playerLoaderManager = std::make_shared<PlayerLoaderManager>(
			_modules,
			_scene.get(),
			_mapMovementManager.get(),
			_playerInputSystem.get(),
			_gameplayEntities.get()
			);
		_playerLoaderManager->LoadPlayer(loadedMapData.PlayerPosition);

		_ghostsLoaderManager = std::make_shared<GhostsLoaderManager>(
			_modules,
			_scene.get(),
			_mapMovementManager.get(),
			_gameplayEntities.get()
			);
		_ghostsLoaderManager->LoadGhosts(loadedMapData);
		const LoadedGhostsData loadedGhostsData = _ghostsLoaderManager->GetLoadedGhostsData();

		_ghostsPrisionManager = std::make_shared<GhostsPrisionManager>(
			_modules,
			_mapMovementManager.get()
			);
		_ghostsPrisionManager->Setup(loadedMapData, loadedGhostsData);

		co_return;
	}
} // PacMan
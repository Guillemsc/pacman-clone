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
#include "../Gameplay/MapMovement/Systems/MapMovementSystem.h"
#include "../Gameplay/MapMovement/Components/MapMovementComponent.h"
#include "PacMan/Gameplay/Input/Systems/PlayerInputSystem.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"

namespace PacMan
{
	GameplayContext::GameplayContext(GEngine::GEngineCoreModules* modules) : Context(modules, "Gameplay")
	{
	}

	tokoro::Async<void> GameplayContext::OnLoadAsync()
	{
		const std::shared_ptr<GEngine::Entity> tilemapEntity = GetScene().AddWorldEntity().lock();
		tilemapEntity->SetName("Tilemap");
		const std::shared_ptr<GEngine::TiledMap2dRendererComponent> tilemap = tilemapEntity->AddComponent<GEngine::TiledMap2dRendererComponent>().lock();

		const std::weak_ptr<GEngine::TiledMapResource> tilemapResource = _modules->resources->GetResource<GEngine::TiledMapResource>(
			"Tiled/maps/test-map.tmx"
			);

		tilemap->SetTiledMap(tilemapResource);

		_mapMovementManager = std::make_shared<MapMovementManager>(tilemap, "Walkability");
		GEngine::ServiceLocator::Register(_mapMovementManager);

		const std::shared_ptr<GEngine::Entity> playerEntity = GetScene().AddWorldEntity().lock();
		playerEntity->SetName("Player");
		playerEntity->AddComponent<GEngine::Shape2dRendererComponent>();
		playerEntity->GetComponent<GEngine::Shape2dRendererComponent>().lock()->SetLayer(1);
		playerEntity->AddComponent<MapMovementComponent>();

		playerEntity->GetTransform().lock()->SetPosition({0, 0, 0});

		const std::shared_ptr<MapMovementSystem> mapMovementSystem = std::make_shared<MapMovementSystem>(
			_mapMovementManager
		);

		const std::weak_ptr<MapMovementComponent> playerGridMovement = playerEntity->GetComponent<MapMovementComponent>();
		_mapMovementManager->SetGridPosition(playerGridMovement, {10, 10});

		mapMovementSystem->Add(playerGridMovement);

		_modules->systems->AddSystem(mapMovementSystem);

		const std::shared_ptr<PlayerInputSystem> playerInputSystem = std::make_shared<PlayerInputSystem>(
			playerEntity->GetComponent<MapMovementComponent>()
		);
		_modules->systems->AddSystem(playerInputSystem);

		co_await Context::OnLoadAsync();
	}
} // PacMan
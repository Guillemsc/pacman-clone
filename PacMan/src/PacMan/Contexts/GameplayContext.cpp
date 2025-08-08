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
#include "PacMan/Gameplay/Managers/MapMovementManager.h"
#include "PacMan/Gameplay/Systems/GridMovementSystem.h"
#include "PacMan/Gameplay/Systems/PlayerInputSystem.h"
#include "PacMan/Gameplay/Components/GridMovementComponent.h"

namespace PacMan
{
	GameplayContext::GameplayContext() : Context("Gameplay")
	{
	}

	tokoro::Async<void> GameplayContext::OnLoadAsync()
	{
		const std::shared_ptr<GEngine::GEngineCoreApplication> app = GEngine::ServiceLocator::Get<GEngine::GEngineCoreApplication>();
		const std::shared_ptr<GEngine::EntitiesModule> entities = app->Entities().lock();
		const std::shared_ptr<GEngine::GameModule> game = app->Game().lock();
		const std::shared_ptr<GEngine::ResourcesModule> resources = app->Resources().lock();
		const std::shared_ptr<GEngine::SystemsModule> systems = app->Systems().lock();
		const std::shared_ptr<GEngine::CoroutinesModule> coroutines = app->Coroutines().lock();

		const std::shared_ptr<GEngine::Entity> tilemapEntity = GetScene().AddWorldEntity().lock();
		tilemapEntity->SetName("Tilemap");
		const std::shared_ptr<GEngine::TiledMap2dRendererComponent> tilemap = tilemapEntity->AddComponent<GEngine::TiledMap2dRendererComponent>().lock();

		const std::weak_ptr<GEngine::TiledMapResource> tilemapResource = resources->GetResource<GEngine::TiledMapResource>("Tiled/maps/test-map.tmx");

		tilemap->SetTiledMap(tilemapResource);

		_mapMovementManager = std::make_shared<MapMovementManager>(tilemap, 0);
		GEngine::ServiceLocator::Register(_mapMovementManager);

		const std::shared_ptr<GEngine::Entity> playerEntity = GetScene().AddWorldEntity().lock();
		playerEntity->SetName("Player");
		playerEntity->AddComponent<GEngine::Shape2dRendererComponent>();
		playerEntity->GetComponent<GEngine::Shape2dRendererComponent>().lock()->SetLayer(1);
		playerEntity->AddComponent<GridMovementComponent>();

		playerEntity->GetTransform().lock()->SetPosition({0, 0, 0});

		const std::shared_ptr<GridMovementSystem> mapMovementSystem = std::make_shared<GridMovementSystem>(
			tilemapEntity->GetComponent<GEngine::TiledMap2dRendererComponent>()
		);
		mapMovementSystem->Add(playerEntity->GetComponent<GridMovementComponent>());
		systems->AddSystem(mapMovementSystem);

		const std::shared_ptr<PlayerInputSystem> playerInputSystem = std::make_shared<PlayerInputSystem>(
			playerEntity->GetComponent<GridMovementComponent>()
		);
		systems->AddSystem(playerInputSystem);

		co_await Context::OnLoadAsync();
	}
} // PacMan
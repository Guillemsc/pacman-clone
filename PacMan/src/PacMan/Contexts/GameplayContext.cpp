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
#include "PacMan/Components/GridMovementComponent.h"
#include "PacMan/Gameplay/Managers/MapMovementManager.h"
#include "PacMan/Systems/GridMovementSystem.h"
#include "PacMan/Systems/PlayerInputSystem.h"

namespace PacMan
{
	GameplayContext::GameplayContext(): Context("Gameplay")
	{
	}

	tokoro::Async<void> GameplayContext::OnLoadAsync()
	{
		const auto app = GEngine::ServiceLocator::Get<GEngine::GEngineCoreApplication>();
		if (!app) co_return;

		const std::shared_ptr<GEngine::EntitiesModule> entities = app->Entities().lock();
		const std::shared_ptr<GEngine::GameModule> game = app->Game().lock();
		const std::shared_ptr<GEngine::ResourcesModule> resources = app->Resources().lock();
		const std::shared_ptr<GEngine::SystemsModule> systems = app->Systems().lock();
		const std::shared_ptr<GEngine::CoroutinesModule> coroutines = app->Coroutines().lock();

		const auto tilemapEntity = AddWorldEntity();
		tilemapEntity.lock()->SetName("Tilemap");
		auto _tilemap = tilemapEntity.lock()->AddComponent<GEngine::TiledMap2dRendererComponent>();

		auto tilemapResource = resources->GetResource<GEngine::TiledMapResource>("Tiled/maps/test-map.tmx");

		_tilemap.lock()->SetTiledMap(tilemapResource);

		_mapMovementManager = std::make_shared<MapMovementManager>();

		auto _playerEntity = AddWorldEntity();
		_playerEntity.lock()->SetName("Player");
		_playerEntity.lock()->AddComponent<GEngine::Shape2dRendererComponent>();
		_playerEntity.lock()->GetComponent<GEngine::Shape2dRendererComponent>().lock()->SetLayer(1);
		_playerEntity.lock()->AddComponent<GridMovementComponent>();

		_playerEntity.lock()->GetTransform().lock()->SetPosition({0, 0, 0});

		const std::shared_ptr<GridMovementSystem> mapMovementSystem = std::make_shared<GridMovementSystem>(
			tilemapEntity.lock()->GetComponent<GEngine::TiledMap2dRendererComponent>()
		);
		mapMovementSystem->Add(_playerEntity.lock()->GetComponent<GridMovementComponent>());
		systems->AddSystem(mapMovementSystem);

		const std::shared_ptr<PlayerInputSystem> playerInputSystem = std::make_shared<PlayerInputSystem>(
			_playerEntity.lock()->GetComponent<GridMovementComponent>()
		);
		systems->AddSystem(playerInputSystem);

		co_await Context::OnLoadAsync();
	}
} // PacMan
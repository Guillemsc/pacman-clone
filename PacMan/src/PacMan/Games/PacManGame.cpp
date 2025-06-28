//
// Created by guillem on 6/7/25.
//

#include "PacManGame.h"

#include "GEngine/Components/CameraComponent.h"
#include "GEngine/Components/Shape2dRendererComponent.h"
#include "GEngine/Components/Texture2dRendererComponent.h"
#include "GEngine/Components/TiledMap2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Coroutines/CoroutineBuilder.h"
#include "GEngine/Coroutines/NestedCoroutine.h"
#include "GEngine/Coroutines/WaitFramesCoroutine.h"
#include "GEngine/Coroutines/WaitSecondsCoroutine.h"
#include "GEngine/Modules/EntitiesModule.h"
#include "GEngine/Modules/GameModule.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Modules/SystemsModule.h"
#include "GEngine/Resources/TextureResource.h"
#include "GEngine/Resources/TiledMapResource.h"
#include "GEngine/Systems/System.h"
#include "GEngine/Timers/ChronoTimer.h"
#include "PacMan/Systems/MapMovementSystem.h"
#include "spdlog/spdlog.h"

namespace Pacman
{
	class MapMovementSystem;
}

PacManGame::~PacManGame()
{

}

void PacManGame::Init()
{
	const auto app = _app.lock();
	if (!app) return;

	std::shared_ptr<GEngine::EntitiesModule> entities = app->Entities().lock();
	std::shared_ptr<GEngine::GameModule> game = app->Game().lock();
	std::shared_ptr<GEngine::ResourcesModule> resources = app->Resources().lock();
	std::shared_ptr<GEngine::SystemsModule> systems = app->Systems().lock();

	auto cameraEntity = entities->AddEntity();
	cameraEntity.lock()->SetName("Camera");
	cameraEntity.lock()->AddComponent<GEngine::CameraComponent>();
	cameraEntity.lock()->GetTransform().lock()->SetPosition({0, 0, -320});

	const auto tilemapEntity = entities->AddEntity();
	tilemapEntity.lock()->SetName("Tilemap");
	_tilemap = tilemapEntity.lock()->AddComponent<GEngine::TiledMap2dRendererComponent>();

	auto tilemapResource = resources->GetResource<GEngine::TiledMapResource>("Tiled/maps/test-map.tmx");

	_tilemap.lock()->SetTiledMap(tilemapResource);
	_tilemap.lock()->GetLayerGridSize(0);

	_playerEntity = entities->AddEntity();
	_playerEntity.lock()->SetName("Player");
	_playerEntity.lock()->AddComponent<GEngine::Shape2dRendererComponent>();

	_playerEntity.lock()->GetTransform().lock()->SetPosition({0, 0, 0});

	//std::weak_ptr<GEngineCore::TextureResource> texture = resources->GetResource<GEngineCore::TextureResource>("proxy-image.png");
	//textureComponent.lock()->SetTexture(texture);

	std::shared_ptr<Pacman::MapMovementSystem> mapMovementSystem = std::make_shared<Pacman::MapMovementSystem>(
		_playerEntity,
		_tilemap
	);
	//systems->AddSystem(mapMovementSystem);

	const std::shared_ptr<GEngine::Coroutine> coroutine = GEngine::CoroutineBuilder()
		.Add(std::make_shared<GEngine::WaitFramesCoroutine>(4))
		.Add(std::make_shared<GEngine::WaitSecondsCoroutine>(4))
		.Add([]()
		{
			spdlog::info("Coroutine Finished!");
		})
		.Build();

	_runner.Run(coroutine);
}

void PacManGame::Tick()
{
	if (IsKeyPressed(KEY_RIGHT))
	{
		_playerGridPosition.x += 1;
	}

	if (IsKeyPressed(KEY_LEFT))
	{
		_playerGridPosition.x -= 1;
	}

	if (IsKeyPressed(KEY_UP))
	{
		_playerGridPosition.y += 1;
	}

	if (IsKeyPressed(KEY_DOWN))
	{
		_playerGridPosition.y -= 1;
	}

	glm::vec2 worldPosition = _tilemap.lock()->GridPositionToWorldPosition(0, _playerGridPosition, GEngine::CellPosition::CENTER);
	_playerEntity.lock()->GetTransform().lock()->SetPosition({worldPosition.x, worldPosition.y, 0});

	_runner.Tick();
}

void PacManGame::Dispose()
{

}




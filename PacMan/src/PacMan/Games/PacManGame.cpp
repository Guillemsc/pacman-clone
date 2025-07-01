//
// Created by guillem on 6/7/25.
//

#include "PacManGame.h"

#include "GEngine/Components/CameraComponent.h"
#include "GEngine/Components/Shape2dRendererComponent.h"
#include "GEngine/Components/Texture2dRendererComponent.h"
#include "GEngine/Components/TiledMap2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Components/UiShapeRendererComponent.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Coroutines/CoroutineBuilder.h"
#include "GEngine/Coroutines/NestedCoroutine.h"
#include "GEngine/Coroutines/WaitFramesCoroutine.h"
#include "GEngine/Coroutines/WaitSecondsCoroutine.h"
#include "GEngine/Modules/CoroutinesModule.h"
#include "GEngine/Modules/EntitiesModule.h"
#include "GEngine/Modules/GameModule.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Modules/SystemsModule.h"
#include "GEngine/Resources/TextureResource.h"
#include "GEngine/Resources/TiledMapResource.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "GEngine/Systems/System.h"
#include "GEngine/Timers/ChronoTimer.h"
#include "PacMan/Components/GridMovementComponent.h"
#include "PacMan/Contexts/ContextsStack.h"
#include "PacMan/Contexts/GameplayContext.h"
#include "PacMan/Systems/GridMovementSystem.h"
#include "spdlog/spdlog.h"

namespace PacMan
{
	PacManGame::~PacManGame()
	{

	}

	void PacManGame::Init()
	{
		const auto app = _app.lock();
		if (!app) return;

		// Cursed maybe???
		GEngine::ServiceLocator::Register(app);

		std::shared_ptr<GEngine::EntitiesModule> entities = app->Entities().lock();

		const std::shared_ptr<ContextsStack> contextsStack = std::make_shared<ContextsStack>(app->Coroutines());
		GEngine::ServiceLocator::Register(contextsStack);

		contextsStack->Push(std::make_shared<GameplayContext>());

		const auto cameraEntity = entities->AddEntity();
		cameraEntity.lock()->SetName("Camera");
		cameraEntity.lock()->AddComponent<GEngine::CameraComponent>();
		cameraEntity.lock()->GetTransform().lock()->SetPosition({0, 0, -320});

		// ======================================================
		auto _uiEntity = entities->AddEntity(true);
		_uiEntity.lock()->AddComponent<GEngine::UiShapeRendererComponent>();
	}

	void PacManGame::Tick()
	{

	}

	void PacManGame::Dispose()
	{
		GEngine::ServiceLocator::Clear();
	}
}




//
// Created by guillem on 6/7/25.
//

#include "PacManGame.h"

#include <iostream>

#include "GEngine/Components/Camera2dComponent.h"
#include "GEngine/Components/CameraComponent.h"
#include "GEngine/Components/Shape2dRendererComponent.h"
#include "GEngine/Components/Texture2dRendererComponent.h"
#include "GEngine/Components/TiledMap2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Components/UiShapeButtonComponent.h"
#include "GEngine/Components/UiShapeRendererComponent.h"
#include "GEngine/Components/UiTextRendererComponent.h"
#include "GEngine/Components/UiTransformComponent.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Coroutines/Coroutines.h"
#include "GEngine/Data/JsonData.h"
#include "GEngine/Modules/EntitiesModule.h"
#include "GEngine/Modules/GameModule.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Modules/TickablesModule.h"
#include "GEngine/Resources/JsonResource.h"
#include "GEngine/Resources/TextureResource.h"
#include "GEngine/Resources/TiledMapResource.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "GEngine/Tickables/Tickable.h"
#include "GEngine/Timers/ChronoTimer.h"
#include "PacMan/Contexts/ContextsStack.h"
#include "PacMan/Contexts/GameplayContext.h"
#include "PacMan/Contexts/MetaContext.h"
#include "PacMan/Contexts/SharedContext.h"
#include "spdlog/spdlog.h"

namespace PacMan
{
	void PacManGame::Init()
	{
		_contextsStack = std::make_unique<ContextsStack>();
		GEngine::ServiceLocator::Register(_contextsStack.get());

		const auto cameraEntity = _modules->entities->AddWorldEntity();
		cameraEntity.lock()->SetName("Camera");
		cameraEntity.lock()->AddComponent<GEngine::Camera2dComponent>().lock()->SetHorizontalFov(350);
		cameraEntity.lock()->GetTransform().lock()->SetPosition({0, 0, 0});

		GEngine::Coroutines::Start(&PacManGame::LaunchGameAsync, this).Forget();
	}

	void PacManGame::Tick(float deltaTime)
	{

	}

	void PacManGame::Dispose()
	{
		GEngine::ServiceLocator::Clear();
	}

	tokoro::Async<void> PacManGame::LaunchGameAsync()
	{
		ContextsStack* contextsStack = GEngine::ServiceLocator::Get<ContextsStack>();

		co_await contextsStack->PushAsync(std::make_shared<SharedContext>(_modules));
		co_await contextsStack->PushAsync(std::make_shared<MetaContext>(_modules));
	}
}




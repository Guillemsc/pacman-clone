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
#include "GEngine/Coroutines/CoroutineBuilder.h"
#include "GEngine/Coroutines/Coroutines.h"
#include "GEngine/Coroutines/NestedCoroutine.h"
#include "GEngine/Coroutines/WaitFramesCoroutine.h"
#include "GEngine/Coroutines/WaitSecondsCoroutine.h"
#include "GEngine/Data/JsonData.h"
#include "GEngine/Modules/CoroutinesModule.h"
#include "GEngine/Modules/EntitiesModule.h"
#include "GEngine/Modules/GameModule.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Modules/SystemsModule.h"
#include "GEngine/Resources/JsonResource.h"
#include "GEngine/Resources/TextureResource.h"
#include "GEngine/Resources/TiledMapResource.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "GEngine/Systems/System.h"
#include "GEngine/Timers/ChronoTimer.h"
#include "../Gameplay/MapMovement/Components/MapMovementComponent.h"
#include "PacMan/Contexts/ContextsStack.h"
#include "PacMan/Contexts/GameplayContext.h"
#include "PacMan/Contexts/MetaContext.h"
#include "PacMan/Contexts/SharedContext.h"
#include "spdlog/spdlog.h"

namespace PacMan
{
	void PacManGame::Init()
	{
		const std::shared_ptr<ContextsStack> contextsStack = std::make_shared<ContextsStack>(_modules->coroutines->AddSequencer());
		GEngine::ServiceLocator::Register(contextsStack);

		const auto cameraEntity = _modules->entities->AddWorldEntity();
		cameraEntity.lock()->SetName("Camera");
		cameraEntity.lock()->AddComponent<GEngine::Camera2dComponent>().lock()->SetHorizontalFov(350);
		cameraEntity.lock()->GetTransform().lock()->SetPosition({0, 0, 0});

		GEngine::Coroutines::Start(&PacManGame::LaunchGameAsync, this).Forget();

		// ======================================================

		// auto _uiEntity2 = entities->AddUiEntity();
		// _uiEntity2.lock()->AddComponent<GEngine::UiShapeRendererComponent>();
		// _uiEntity2.lock()->AddComponent<GEngine::UiShapeButtonComponent>();
		// _uiEntity2.lock()->GetComponent<GEngine::UiShapeRendererComponent>().lock()->SetColor( {1, 0, 0, 1} );
		//_uiEntity2.lock()->GetUiTransform().lock()->SetSizeDelta({0, 0});
		// _uiEntity2.lock()->GetUiTransform().lock()->SetPivot({0, 0});

		// auto _uiEntity = entities->AddUiEntity();
		// _uiEntity.lock()->AddComponent<GEngine::UiShapeRendererComponent>();
		// _uiEntity.lock()->AddComponent<GEngine::UiShapeButtonComponent>();
		// _uiEntity.lock()->GetUiTransform().lock()->SetAnchoredPosition({0, 0});
		// _uiEntity.lock()->GetUiTransform().lock()->SetSizeDelta({0, 0});
		// _uiEntity.lock()->GetUiTransform().lock()->SetAnchors({0.0f, .0f, 1.0f, 1});
		//
		// _uiEntity2.lock()->GetUiTransform().lock()->SetAnchors({0.2, 0.2, 0.8, 0.8});
		//
		// _uiEntity2.lock()->SetParent(_uiEntity);

		// auto _textEntity = entities->AddUiEntity();
		// _textEntity.lock()->AddComponent<GEngine::UiTextRendererComponent>();

		// const std::shared_ptr<GEngine::ResourcesModule> resources = app->Resources().lock();
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
		const std::shared_ptr<ContextsStack> contextsStack = GEngine::ServiceLocator::Get<ContextsStack>();

		co_await contextsStack->PushAsync(std::make_shared<SharedContext>(_modules));
		co_await contextsStack->PushAsync(std::make_shared<MetaContext>(_modules));
	}
}




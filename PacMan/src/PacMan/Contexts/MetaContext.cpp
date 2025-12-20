//
// Created by guillem on 7/26/25.
//

#include "MetaContext.h"

#include "ContextsStack.h"
#include "GameplayContext.h"
#include "GEngine/Components/UiShapeButtonComponent.h"
#include "GEngine/Components/UiShapeRendererComponent.h"
#include "GEngine/Components/UiTextRendererComponent.h"
#include "GEngine/Components/UiTransformComponent.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Coroutines/CancellationToken.h"
#include "GEngine/Coroutines/CoroutinesRunner.h"
#include "GEngine/Modules/CoroutinesModule.h"
#include "GEngine/Modules/EntitiesModule.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "spdlog/spdlog.h"

namespace PacMan
{
	MetaContext::MetaContext(GEngine::GEngineCoreModules* modules, const bool returningFromGameplay)
		: Context(modules, "Meta"), _returningFromGameplay(returningFromGameplay)
	{
	}

	tokoro::Async<void> MetaContext::OnLoadAsync()
	{
		std::unique_ptr<SplashManager> splashManager = std::make_unique<SplashManager>(
			_modules,
			_scene.get()
			);

		std::unique_ptr<MainMenuManager> mainMenuManager = std::make_unique<MainMenuManager>(
			_modules,
			_scene.get()
			);

		_splashManager = std::move(splashManager);
		_mainMenuManager = std::move(mainMenuManager);

		co_await Context::OnLoadAsync();
	}

	void MetaContext::OnStart()
	{
		GetCoroutinesRunner()->Start(&MetaContext::StartFromSplashAsync, this, GEngine::CancellationToken::None()).Forget();
	}

	void MetaContext::OnDispose()
	{

	}

	tokoro::Async<void> MetaContext::StartFromSplashAsync(const GEngine::CancellationToken cancellationToken) const
	{
		if (!_returningFromGameplay)
		{
			co_await _splashManager->PlaySplashAsync(cancellationToken);
		}

		co_await _mainMenuManager->ShowAsync(cancellationToken);
	}
}

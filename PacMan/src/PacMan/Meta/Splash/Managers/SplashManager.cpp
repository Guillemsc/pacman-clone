//
// Created by guillem on 12/19/25.
//

#include "SplashManager.h"

#include "GEngine/Coroutines/CancellationToken.h"
#include "GEngine/Timers/ChronoTimer.h"
#include "PacMan/Meta/Splash/Views/SplashUiView.h"

namespace PacMan
{
	SplashManager::SplashManager(GEngine::GEngineCoreModules* modules, GEngine::Scene *scene)
		: _modules(modules), _scene(scene)
	{
	}

	tokoro::Async<void> SplashManager::PlaySplashAsync(const GEngine::CancellationToken cancellationToken) const
	{
		const std::shared_ptr<SplashUiView> splashView = UiView::Create<SplashUiView>(_modules, _scene);

		co_await GEngine::ChronoTimer::AwaitSeconds(0.3f, cancellationToken);
		co_await splashView->PlaySplashAsync(cancellationToken);

		splashView->Dispose();
	}
} // PacMan
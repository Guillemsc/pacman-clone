//
// Created by guillem on 12/19/25.
//

#include "SplashManager.h"

#include "GEngine/Coroutines/CancellationToken.h"
#include "GEngine/Timers/ChronoTimer.h"
#include "PacMan/Meta/Splash/Views/SplashView.h"

namespace PacMan
{
	SplashManager::SplashManager(GEngine::Scene *scene)
		: _scene(scene)
	{
	}

	tokoro::Async<void> SplashManager::PlaySplashAsync(const GEngine::CancellationToken cancellationToken) const
	{
		const std::shared_ptr<SplashView> splashView = SplashView::Load(_scene);

		co_await GEngine::ChronoTimer::AwaitSeconds(5, cancellationToken);

		splashView->Dispose();
	}
} // PacMan
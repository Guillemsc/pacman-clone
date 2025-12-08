//
// Created by guillem on 6/28/25.
//

#include "ChronoTimer.h"

#include "ChronoTimeSource.h"
#include "GEngine/Coroutines/CancellationToken.h"

namespace GEngine
{
	ChronoTimer::ChronoTimer(): Timer(std::make_shared<ChronoTimeSource>())
	{

	}

	std::shared_ptr<ChronoTimer> ChronoTimer::FromStarted()
	{
		std::shared_ptr<ChronoTimer> timer = std::make_shared<ChronoTimer>();
		timer->Start();
		return timer;
	}

	tokoro::Async<void> ChronoTimer::AwaitSeconds(const float seconds, const CancellationToken cancellationToken)
	{
		const std::shared_ptr<ChronoTimer> timer = FromStarted();

		while (timer->GetTimeSeconds() < seconds)
		{
			if (cancellationToken.IsCancelled()) break;
			co_await tokoro::Wait();
		}
	}
} // GengineCore
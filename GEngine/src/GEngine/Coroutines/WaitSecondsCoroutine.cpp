//
// Created by guillem on 6/28/25.
//

#include "WaitSecondsCoroutine.h"

#include "GEngine/Timers/ChronoTimer.h"

namespace GEngine
{
	WaitSecondsCoroutine::WaitSecondsCoroutine(const double seconds)
	{
		_seconds = seconds;
		_timer = std::make_unique<ChronoTimer>();
	}

	bool WaitSecondsCoroutine::MoveNext()
	{
		_timer->Start();

		const double currentSeconds = _timer->GetTimeSeconds();
		const double secondsLeft = _seconds - currentSeconds;

		return secondsLeft > 0;
	}
} // GEngineCore
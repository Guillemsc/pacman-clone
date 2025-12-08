//
// Created by guillem on 6/28/25.
//

#ifndef CHRONOTIMER_H
#define CHRONOTIMER_H

#include "Timer.h"
#include "tokoro.h"

namespace GEngine
{
	class CancellationToken;

	class ChronoTimer : public Timer
	{
	public:
		ChronoTimer();

		static std::shared_ptr<ChronoTimer> FromStarted();
		static tokoro::Async<void> AwaitSeconds(float seconds, CancellationToken cancellationToken);
	};
}

#endif //CHRONOTIMER_H

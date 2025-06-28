//
// Created by guillem on 6/28/25.
//

#include "ChronoTimer.h"

#include "ChronoTimeSource.h"

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
} // GengineCore
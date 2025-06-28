//
// Created by guillem on 6/28/25.
//

#ifndef CHRONOTIMER_H
#define CHRONOTIMER_H

#include "Timer.h"

namespace GEngine
{
	class ChronoTimer : public Timer
	{
	public:
		ChronoTimer();

		static std::shared_ptr<ChronoTimer> FromStarted();
	};
}

#endif //CHRONOTIMER_H

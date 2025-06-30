//
// Created by guillem on 6/28/25.
//

#include "TimeSlicedCoroutine.h"

#include "GEngine/Timers/ChronoTimer.h"

namespace GEngine
{
	TimeSlicedCoroutine::TimeSlicedCoroutine(const double secondsBudget)
	{
		_secondsBudget = secondsBudget;
		_timer = std::make_unique<ChronoTimer>();
	}

	bool TimeSlicedCoroutine::MoveNext()
	{
		_timer->Reset();

		bool shouldTimeSlice = false;

		while (!shouldTimeSlice)
		{
			const bool canContinue = MoveNextTimeSliced();

			if (canContinue)
			{
				return true;
			}

			shouldTimeSlice = _timer->GetTimeSeconds() >= _secondsBudget;
		}

		return false;
	}
} // GEngineCore
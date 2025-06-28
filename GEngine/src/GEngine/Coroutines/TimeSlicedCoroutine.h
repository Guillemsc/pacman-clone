//
// Created by guillem on 6/28/25.
//

#ifndef TIMESLICEDCOROUTINE_H
#define TIMESLICEDCOROUTINE_H

#include <memory>

#include "Coroutine.h"

namespace GEngine
{
	class ChronoTimer;

	class TimeSlicedCoroutine : public Coroutine
	{
	public:
		TimeSlicedCoroutine(double secondsBudget);

		bool MoveNext() override;

	protected:
		virtual bool MoveNextTimeSliced() = 0;

	private:
		double _secondsBudget = 0;
		std::unique_ptr<ChronoTimer> _timer;
	};
}

#endif //TIMESLICEDCOROUTINE_H

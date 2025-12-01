//
// Created by guillem on 6/28/25.
//

#ifndef TIMER_H
#define TIMER_H

#include <memory>

#include "ITimeSource.h"

namespace GEngine
{
	class Timer
	{
	public:
		explicit Timer(const std::shared_ptr<ITimeSource>& timeSource);

		double GetTimeSeconds() const;

		void Start();
		void Reset();
		void Restart();

		bool IsStarted() const;

	private:
		std::shared_ptr<ITimeSource> _timeSource;

		double _startSeconds = 0;
		bool _isStarted = false;
	};
}

#endif //TIMER_H

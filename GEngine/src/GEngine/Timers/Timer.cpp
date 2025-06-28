//
// Created by guillem on 6/28/25.
//

#include "Timer.h"

namespace GEngine
{
	Timer::Timer(const std::shared_ptr<ITimeSource> &timeSource)
	{
		_timeSource = timeSource;
	}

	double Timer::GetTimeSeconds() const
	{
		if (!_isStarted) return 0;

		const double time = _timeSource->GetTimeSeconds() - _startSeconds;

		return time;
	}

	void Timer::Start()
	{
		if (_isStarted) return;

		_isStarted = true;

		_startSeconds = _timeSource->GetTimeSeconds();
	}

	void Timer::Reset()
	{
		_isStarted = false;
		_startSeconds = 0;
	}

	void Timer::Restart()
	{
		Reset();
		Start();
	}

	bool Timer::IsStarted() const
	{
		return _isStarted;
	}
} // GEngineCore
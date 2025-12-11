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
		_isPaused = false;
		_startSeconds = 0;
		_pauseStartSeconds = 0;
	}

	void Timer::Restart()
	{
		Reset();
		Start();
	}

	void Timer::Pause()
	{
		if (!_isStarted) return;
		if (_isPaused) return;

		_isPaused = true;
		_pauseStartSeconds = _timeSource->GetTimeSeconds();
	}

	void Timer::Resume()
	{
		if (!_isStarted) return;
		if (!_isPaused) return;

		_isPaused = false;

		const float pausedSecondsPassed = _timeSource->GetTimeSeconds() - _pauseStartSeconds;
		_startSeconds += pausedSecondsPassed;
		_pauseStartSeconds = 0;
	}

	bool Timer::IsStarted() const
	{
		return _isStarted;
	}

	bool Timer::IsPaused() const
	{
		return _isPaused;
	}
} // GEngineCore
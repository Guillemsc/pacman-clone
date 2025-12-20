//
// Created by guillem on 12/19/25.
//

#include "WaitTween.h"

namespace GEngine
{
	WaitTween::WaitTween(const float duration)
	{
		_duration = duration;
	}

	void WaitTween::OnStart()
	{
		_currentTime = 0;
	}

	void WaitTween::OnTick(const float deltaTime)
	{
		_currentTime += deltaTime;

		if (_currentTime >= _duration)
		{
			CompleteMain();
		}
	}
}

//
// Created by guillem on 6/28/25.
//

#include "WaitFramesCoroutine.h"

namespace GEngine
{
	WaitFramesCoroutine::WaitFramesCoroutine(const int frames)
	{
		_framesLeft = frames;
	}

	bool WaitFramesCoroutine::MoveNext()
	{
		_framesLeft -= 1;

		return _framesLeft <= 0;
	}
} // GEngineCore
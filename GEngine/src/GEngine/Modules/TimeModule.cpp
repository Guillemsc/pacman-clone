//
// Created by guillem on 7/12/25.
//

#include "TimeModule.h"

#include "GEngine/Raylib/RaylibWrapper.h"

namespace GEngine
{
	float TimeModule::GetDeltaTime() const
	{
		return GetFrameTime();
	}

	int TimeModule::GetFps() const
	{
		return GetFPS();
	}
} // GEngine
//
// Created by guillem on 7/12/25.
//

#include "TimeModule.h"

#include "raylib.h"

namespace GEngine
{
	float TimeModule::GetDeltaTime() const
	{
		return GetFrameTime();
	}
} // GEngine
//
// Created by guillem on 7/27/25.
//

#include "Coroutines.h"

namespace GEngine
{
	tokoro::Scheduler & Coroutines::Scheduler()
	{
		static tokoro::Scheduler s;
		return s;
	}
}

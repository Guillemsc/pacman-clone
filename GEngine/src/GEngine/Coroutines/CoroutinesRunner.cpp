//
// Created by guillem on 12/4/25.
//

#include "CoroutinesRunner.h"

namespace GEngine
{
	void CoroutinesRunner::Tick()
	{
		_scheduler.Update();
	}
}

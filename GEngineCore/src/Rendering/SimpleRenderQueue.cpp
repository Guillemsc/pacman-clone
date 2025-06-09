//
// Created by guillem on 6/9/25.
//

#include "SimpleRenderQueue.h"

namespace GEngineCore
{
	void SimpleRenderQueue::Add(const std::function<void()> &func)
	{
		_queue.push_back(func);
	}

	void SimpleRenderQueue::Execute()
	{
		for (auto it = _queue.begin(); it != _queue.end(); ++it)
		{
			(*it)();
		}

		_queue.clear();
	}
} // GEngineCore
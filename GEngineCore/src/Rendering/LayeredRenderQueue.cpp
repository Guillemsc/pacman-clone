//
// Created by guillem on 6/7/25.
//

#include "LayeredRenderQueue.h"

#include "Extensions/MapExtensions.h"

namespace GEngineCore
{
	void LayeredRenderQueue::Add(const std::int32_t layer, const std::function<void()> &func)
	{
		_queue[layer].push_back(func);
	}

	void LayeredRenderQueue::Execute()
	{
		for (auto it = _queue.begin(); it != _queue.end(); ++it)
		{
			std::vector<std::function<void()>>& funcs = it->second;

			for (auto funcsIt = funcs.rbegin(); funcsIt != funcs.rend(); ++funcsIt)
			{
				(*funcsIt)();
			}
		}

		_queue.clear();
	}
} // GEngineCore
//
// Created by guillem on 6/7/25.
//

#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

#include <cstdint>
#include <functional>
#include <map>
#include <vector>

namespace GEngineCore
{
	class LayeredRenderQueue
	{
	public:
		void Add(std::int32_t layer, const std::function<void()> &func);
		void Execute();

	private:
		std::map<std::int32_t, std::vector<std::function<void()>>> _queue;
	};
}

#endif //RENDERQUEUE_H

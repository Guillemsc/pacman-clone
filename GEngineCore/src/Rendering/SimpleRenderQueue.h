//
// Created by guillem on 6/9/25.
//

#ifndef SIMPLERENDERQUEUE_H
#define SIMPLERENDERQUEUE_H

#include <functional>
#include <vector>

namespace GEngineCore
{
	class SimpleRenderQueue
	{
	public:
		void Add(const std::function<void()> &func);
		void Execute();

	private:
		std::vector<std::function<void()>> _queue;
	};
}
#endif //SIMPLERENDERQUEUE_H

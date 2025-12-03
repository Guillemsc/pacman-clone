//
// Created by guillem on 6/30/25.
//

#ifndef CONTEXTSSTACK_H
#define CONTEXTSSTACK_H

#include <memory>
#include <vector>

#include "tokoro.h"

namespace GEngine
{
	class CoroutineSequencer;
	class CoroutinesModule;
}

namespace PacMan
{
	class Context;

	class ContextsStack
	{
	public:
		tokoro::Async<void> PushAsync(std::shared_ptr<Context> context);
		void Pop();

	private:
		std::vector<std::shared_ptr<Context>> _contextsStack;

		bool _loading = false;
	};
}

#endif //CONTEXTSSTACK_H

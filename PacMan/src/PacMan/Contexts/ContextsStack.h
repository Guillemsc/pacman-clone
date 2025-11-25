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
		explicit ContextsStack(const std::weak_ptr<GEngine::CoroutineSequencer>& coroutineSequencer);

		tokoro::Async<void> PushAsync(const std::shared_ptr<Context> &context);
		void Pop();

	private:
		const std::weak_ptr<GEngine::CoroutineSequencer> _coroutineSequencer;
		std::vector<std::shared_ptr<Context>> _contextsStack;

		bool _loading = false;
		std::shared_ptr<Context> _pushingContext;
	};
}

#endif //CONTEXTSSTACK_H

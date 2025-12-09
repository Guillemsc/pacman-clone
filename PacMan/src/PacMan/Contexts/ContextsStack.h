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
	class GEngineCoreModules;
}

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
		ContextsStack(GEngine::GEngineCoreModules* modules);

		tokoro::Async<void> PushAsync(std::shared_ptr<Context> context);
		void Pop();

	private:
		GEngine::GEngineCoreModules* const _modules;

		std::vector<std::shared_ptr<Context>> _contextsStack;
		std::vector<std::shared_ptr<Context>> _poppingContexts;

		bool _loading = false;
	};
}

#endif //CONTEXTSSTACK_H

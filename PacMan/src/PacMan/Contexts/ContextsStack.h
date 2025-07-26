//
// Created by guillem on 6/30/25.
//

#ifndef CONTEXTSSTACK_H
#define CONTEXTSSTACK_H

#include <memory>
#include <vector>

namespace GEngine
{
	class CoroutinesModule;
}

namespace PacMan
{
	class Context;

	class ContextsStack
	{
	public:
		explicit ContextsStack(const std::weak_ptr<GEngine::CoroutinesModule> &coroutinesModule);

		void Push(const std::shared_ptr<Context> &context);
		void Pop();

	private:
		std::weak_ptr<GEngine::CoroutinesModule> _coroutinesPtr;
		std::vector<std::shared_ptr<Context>> _contextsStack;

		bool _loading = false;
	};
}

#endif //CONTEXTSSTACK_H

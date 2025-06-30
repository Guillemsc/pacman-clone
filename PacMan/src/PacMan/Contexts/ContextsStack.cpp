//
// Created by guillem on 6/30/25.
//

#include "ContextsStack.h"

#include "Context.h"
#include "GEngine/Coroutines/CoroutineBuilder.h"
#include "GEngine/Modules/CoroutinesModule.h"

namespace PacMan
{
	ContextsStack::ContextsStack(const std::weak_ptr<GEngine::CoroutinesModule> &coroutinesModule)
	{
		_coroutinesPtr = coroutinesModule;
	}

	void ContextsStack::Push(const std::shared_ptr<Context> &context)
	{
		const std::shared_ptr<GEngine::CoroutinesModule> coroutines = _coroutinesPtr.lock();
		if (!coroutines) return;;

		if (_loading) return;

		const std::shared_ptr<GEngine::Coroutine> loadCoroutine = context->Load();

		_loading = true;

		const GEngine::CoroutineBuilder builder;

		builder
			.Add(loadCoroutine)
			.Add([this, context]()
			{
				_loading = false;
				_contextsStack.push_back(context);
			});

		coroutines->Run(builder.Build());
	}
} // PacMan
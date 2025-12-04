//
// Created by guillem on 6/30/25.
//

#include "ContextsStack.h"

#include "Context.h"
#include "GEngine/Extensions/VectorExtensions.h"

namespace PacMan
{
	tokoro::Async<void> ContextsStack::PushAsync(const std::shared_ptr<Context> context)
	{
		if (_loading) co_return;

		_loading = true;

		co_await context->LoadAsync();

		_contextsStack.push_back(context);

		_loading = false;
	}

	void ContextsStack::Pop()
	{
		if (_contextsStack.empty()) return;

		const std::shared_ptr<Context> context = _contextsStack.back();
		GEngine::VectorExtensions::Remove(_contextsStack, context);

		context->Dispose();
	}
} // PacMan
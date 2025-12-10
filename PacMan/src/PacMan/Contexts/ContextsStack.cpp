//
// Created by guillem on 6/30/25.
//

#include "ContextsStack.h"

#include "Context.h"
#include "GEngine/Extensions/VectorExtensions.h"
#include "GEngine/Logging/GEngineLog.h"
#include "GEngine/Modules/DeferredExecutionModule.h"

namespace PacMan
{
	ContextsStack::ContextsStack(GEngine::GEngineCoreModules* modules)
		: _modules(modules)
	{

	}

	tokoro::Async<void> ContextsStack::PushAsync(const std::shared_ptr<Context> context)
	{
		if (_loading) co_return;

		_loading = true;

		GENGINE_INFO("Pushing context {}", context->GetName());

		co_await context->LoadAsync();

		_contextsStack.push_back(context);

		_loading = false;
	}

	void ContextsStack::Pop()
	{
		if (_loading) return;
		if (_contextsStack.empty()) return;

		const std::shared_ptr<Context> context = _contextsStack.back();

		GENGINE_INFO("Popping context {}", context->GetName());

		GEngine::VectorExtensions::Remove(_contextsStack, context);

		context->Dispose();

		_poppingContexts.push_back(context);

		_modules->deferredExecution->Push([this, &context]
		{
			GEngine::VectorExtensions::Remove(_poppingContexts, context);
		});
	}
} // PacMan
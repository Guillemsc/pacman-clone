//
// Created by guillem on 6/30/25.
//

#include "Context.h"

#include "GEngine/Coroutines/CoroutineBuilder.h"

namespace PacMan
{
	std::shared_ptr<GEngine::Coroutine> Context::Load()
	{
		if (_loaded) return GEngine::Coroutine::Empty();

		_disposed = false;
		_started = false;
		_loaded = true;

		return OnLoad();
	}

	void Context::Start()
	{
		if (!_loaded) return;
		if (_started) return;

		_started = true;

		OnStart();
	}

	void Context::Dispose()
	{
		if (!_loaded) return;
		if (_disposed) return;

		_loaded = false;
		_disposed = true;

		OnDispose();
	}

	std::shared_ptr<GEngine::Coroutine> Context::OnLoad()
	{
		return GEngine::Coroutine::Empty();
	}

	void Context::OnStart()
	{
	}

	void Context::OnDispose()
	{
	}
}

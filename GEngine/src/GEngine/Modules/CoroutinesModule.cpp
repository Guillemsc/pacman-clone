//
// Created by guillem on 6/30/25.
//

#include "CoroutinesModule.h"

#include "GEngine/Coroutines/CoroutineRunner.h"

namespace GEngine
{
	CoroutinesModule::CoroutinesModule()
	{
		_coroutineRunner = std::make_shared<CoroutineRunner>();
	}

	void CoroutinesModule::Tick()
	{
		_coroutineRunner->Tick();
	}

	std::weak_ptr<CoroutineTask> CoroutinesModule::Run(const std::shared_ptr<Coroutine> &coroutine) const
	{
		return _coroutineRunner->Run(coroutine);
	}
} // GEngine

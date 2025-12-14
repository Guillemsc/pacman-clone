//
// Created by guillem on 12/4/25.
//

#include "CoroutinesModule.h"

#include "GEngine/Coroutines/CoroutinesRunner.h"
#include "GEngine/Extensions/VectorExtensions.h"

namespace GEngine
{
	void CoroutinesModule::Init(GEngineCoreModules *modules)
	{
		_modules = modules;
		_mainRunner = std::make_shared<CoroutinesRunner>();
	}

	void CoroutinesModule::Tick() const
	{
		_mainRunner->Tick();

		for (int i = _runners.size() - 1; i >= 0; i--)
		{
			_runners[i]->Tick();
		}
	}

	void CoroutinesModule::Dispose()
	{
		_mainRunner.reset();
		_runners.clear();
	}

	CoroutinesRunner* CoroutinesModule::GetMainRunner() const
	{
		return _mainRunner.get();
	}

	std::weak_ptr<CoroutinesRunner> CoroutinesModule::CreateRunner()
	{
		const std::shared_ptr<CoroutinesRunner> runner = std::make_shared<CoroutinesRunner>();
		_runners.push_back(runner);
		return runner;
	}

	void CoroutinesModule::DestroyRunner(const std::weak_ptr<CoroutinesRunner> &runner)
	{
		const std::shared_ptr<CoroutinesRunner> lRunner = runner.lock();
		if (!lRunner) return;

		VectorExtensions::Remove(_runners, lRunner);
	}
}

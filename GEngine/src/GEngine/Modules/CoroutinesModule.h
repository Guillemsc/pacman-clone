//
// Created by guillem on 12/4/25.
//

#ifndef COROUTINESMODULE_H
#define COROUTINESMODULE_H

#include <memory>
#include <vector>

#include "tokoro.h"

namespace GEngine
{
	class CoroutinesRunner;
	class GEngineCoreModules;

	class CoroutinesModule
	{
	public:
		void Init(GEngineCoreModules* modules);
		void Tick() const;
		void Dispose();

		std::weak_ptr<CoroutinesRunner> CreateRunner();
		void DestroyRunner(const std::weak_ptr<CoroutinesRunner>& runner);

	private:
		GEngineCoreModules* _modules = nullptr;

		std::vector<std::shared_ptr<CoroutinesRunner>> _runners;
	};
}

#endif //COROUTINESMODULE_H

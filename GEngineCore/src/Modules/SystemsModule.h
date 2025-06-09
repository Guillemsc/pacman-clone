//
// Created by guillem on 6/8/25.
//

#ifndef SYSTEMSMODULE_H
#define SYSTEMSMODULE_H
#include <memory>
#include <vector>

namespace GEngineCore
{
	class GEngineCoreApplication;
	class System;

	class SystemsModule
	{
	public:
		SystemsModule();

		void Init(const std::weak_ptr<GEngineCoreApplication>& app);
		void Tick();
		void Dispose();

		void AddSystem(const std::shared_ptr<System>& system);

	private:
		void TickSystems();

	private:
		std::vector<std::shared_ptr<System>> _systems;
	};
}

#endif //SYSTEMSMODULE_H

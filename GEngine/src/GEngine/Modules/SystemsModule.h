//
// Created by guillem on 6/8/25.
//

#ifndef SYSTEMSMODULE_H
#define SYSTEMSMODULE_H
#include <memory>
#include <vector>

#include "GEngine/Core/GEngineCoreModules.h"

namespace GEngine
{
	class GEngineCoreApplication;
	class System;

	class SystemsModule
	{
	public:
		SystemsModule();

		void Init(GEngineCoreModules* modules);
		void Tick();
		void Dispose();

		void AddSystem(const std::shared_ptr<System>& system);

		void RemoveAllSystemsNow();

	private:
		void TickSystems();

	private:
		std::vector<std::shared_ptr<System>> _systems;
	};
}

#endif //SYSTEMSMODULE_H

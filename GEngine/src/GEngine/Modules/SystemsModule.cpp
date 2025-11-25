//
// Created by guillem on 6/8/25.
//

#include "SystemsModule.h"

#include "GEngine/Systems/System.h"
#include "GEngine/Systems/TickShapeRenderer2dComponentsSystem.h"

namespace GEngine
{
	SystemsModule::SystemsModule()
	{

	}

	void SystemsModule::Init(GEngineCoreModules* modules)
	{
		AddSystem(std::make_shared<TickShapeRenderer2dComponentsSystem>(modules));
	}

	void SystemsModule::Tick()
	{
		TickSystems();
	}

	void SystemsModule::Dispose()
	{
		_systems.clear();
	}

	void SystemsModule::AddSystem(const std::shared_ptr<System>& system)
	{
		_systems.push_back(system);
	}

	void SystemsModule::RemoveAllSystemsNow()
	{
		_systems.clear();
	}

	void SystemsModule::TickSystems()
	{
		for (auto it = _systems.begin(); it != _systems.end(); ++it)
		{
			(*it)->Tick();
		}
	}
} // GEngineCore
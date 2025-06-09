//
// Created by guillem on 6/8/25.
//

#include "SystemsModule.h"

#include "Systems/System.h"
#include "Systems/TickShapeRenderer2dComponentsSystem.h"

namespace GEngineCore
{
	SystemsModule::SystemsModule()
	{

	}

	void SystemsModule::Init(const std::weak_ptr<GEngineCoreApplication>& app)
	{
		AddSystem(std::make_shared<TickShapeRenderer2dComponentsSystem>(app));
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

	void SystemsModule::TickSystems()
	{
		for (auto it = _systems.begin(); it != _systems.end(); ++it)
		{
			(*it)->Tick();
		}
	}
} // GEngineCore
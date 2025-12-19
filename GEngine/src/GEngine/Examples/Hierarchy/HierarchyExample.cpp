//
// Created by guillem on 12/19/25.
//

#include "HierarchyExample.h"

#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Modules/EntitiesModule.h"

namespace GEngine
{
	HierarchyExample::HierarchyExample() : Game("Hierarchy Example")
	{
	}

	void HierarchyExample::Init()
	{
		const std::shared_ptr<Entity> entity0 = _modules->entities->AddWorldEntity().lock();

		const std::shared_ptr<Entity> entity1 = _modules->entities->AddWorldEntity().lock();
		const std::shared_ptr<Entity> entity2 = _modules->entities->AddWorldEntity(entity1).lock();
		const std::shared_ptr<Entity> entity3 = _modules->entities->AddWorldEntity(entity2).lock();

		const std::shared_ptr<Entity> entity4 = _modules->entities->AddWorldEntity().lock();
	}

	void HierarchyExample::Tick(float deltaTime)
	{
	}

	void HierarchyExample::Dispose()
	{
	}
}

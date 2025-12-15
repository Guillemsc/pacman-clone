//
// Created by guillem on 12/15/25.
//

#include "Pools.h"

namespace GEngine
{
	ObjectPool<std::vector<std::shared_ptr<Entity>>> Pools::entitiesVector;

	void Pools::Init()
	{
		entitiesVector.SetWhenReset([](std::vector<std::shared_ptr<Entity>>* vector)
		{
			vector->clear();
		});
	}

	void Pools::Dispose()
	{
		entitiesVector.Clear();
	}
}

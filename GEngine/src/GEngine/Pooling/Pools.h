//
// Created by guillem on 12/15/25.
//

#ifndef POOLS_H
#define POOLS_H

#include "ObjectPool.h"
#include "GEngine/Entities/Entity.h"

namespace GEngine
{
	class Pools
	{
	public:
		static void Init();
		static void Dispose();

	public:
		static ObjectPool<std::vector<std::shared_ptr<Entity>>> entitiesVector;
	};
}

#endif //POOLS_H

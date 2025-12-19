//
// Created by guillem on 12/19/25.
//

#ifndef HIERARCHYEXAMPLE_H
#define HIERARCHYEXAMPLE_H

#include "GEngine/Games/Game.h"

namespace GEngine
{
	class HierarchyExample final : public Game
	{
	public:
		HierarchyExample();

		void Init() override;
		void Tick(float deltaTime) override;
		void Dispose() override;
	};
}

#endif //HIERARCHYEXAMPLE_H

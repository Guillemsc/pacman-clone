//
// Created by guillem on 6/7/25.
//

#ifndef GAME_H
#define GAME_H

#include <memory>

#include "GEngine/Core/GEngineCoreModules.h"

namespace GEngine
{
	class GEngineCoreApplication;

	class Game
	{
	public:
		virtual ~Game() = default;
		void Setup(GEngineCoreModules* modules) { _modules = modules; }

		virtual void Init() = 0;
		virtual void Tick(float deltaTime) = 0;
		virtual void Dispose() = 0;

	protected:
		GEngineCoreModules* _modules;
	};
}

#endif //GAME_H

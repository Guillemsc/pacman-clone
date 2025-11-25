//
// Created by guillem on 6/7/25.
//

#ifndef GAMEMODULE_H
#define GAMEMODULE_H
#include <memory>

#include "GEngine/Core/GEngineCoreModules.h"

namespace GEngine
{
	class GEngineCoreApplication;
	class Game;

	class GameModule
	{
	public:
		GameModule();

		void Init(GEngineCoreModules* modules);
		void Tick() const;
		void Dispose();

		void LoadGame(const std::shared_ptr<Game> &game);

	private:
		GEngineCoreModules* _modules = nullptr;

		std::shared_ptr<Game> _currentGame = nullptr;
	};
}

#endif //GAMEMODULE_H

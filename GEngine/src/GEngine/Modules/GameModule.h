//
// Created by guillem on 6/7/25.
//

#ifndef GAMEMODULE_H
#define GAMEMODULE_H

#include <memory>

namespace GEngine
{
	class GEngineCoreModules;
	class Game;

	class GameModule
	{
	public:
		GameModule();

		void Init(GEngineCoreModules* modules);
		void Tick() const;
		void Dispose();

		// Fires up a new game.
		// - First we unload the previous one, if there was one loaded.
		// - Then we load and run the new one.
		// This is the main way of running an external game loop.
		// Note: should this be shared_ptr? will this be used from the outside?
		void LoadGame(const std::shared_ptr<Game>& game);

	private:
		GEngineCoreModules* _modules = nullptr;

		std::shared_ptr<Game> _currentGame = nullptr;
	};
}

#endif //GAMEMODULE_H

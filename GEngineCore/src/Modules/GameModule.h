//
// Created by guillem on 6/7/25.
//

#ifndef GAMEMODULE_H
#define GAMEMODULE_H
#include <memory>

namespace GEngineCore
{
	class GEngineCoreApplication;
	class Game;

	class GameModule
	{
	public:
		GameModule();

		void Init(const std::weak_ptr<GEngineCoreApplication> &app);
		void Tick();
		void Dispose();

		void LoadGame(const std::shared_ptr<Game> &game);

	private:
		std::weak_ptr<GEngineCoreApplication> _app;

		std::shared_ptr<Game> _currentGame = nullptr;
	};
}

#endif //GAMEMODULE_H

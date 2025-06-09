//
// Created by guillem on 6/7/25.
//

#include "GameModule.h"

#include "Games/Game.h"

namespace GEngineCore
{
	GameModule::GameModule()
	{

	}

	void GameModule::Init(const std::weak_ptr<GEngineCoreApplication> &app)
	{
		_app = app;
	}

	void GameModule::Tick()
	{
		if (_currentGame == nullptr)
		{
			return;
		}

		_currentGame->Tick();
	}

	void GameModule::Dispose()
	{
		if (_currentGame == nullptr)
		{
			return;
		}

		_currentGame->Dispose();
		_currentGame = nullptr;
	}

	void GameModule::LoadGame(const std::shared_ptr<Game> &game)
	{
		if (_currentGame != nullptr)
		{
			_currentGame->Dispose();
		}

		_currentGame = game;

		_currentGame->Setup(_app);
		_currentGame->Init();
	}
} // GEngineCore
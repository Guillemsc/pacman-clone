//
// Created by guillem on 6/7/25.
//

#include "GameModule.h"

#include "EntitiesModule.h"
#include "SystemsModule.h"
#include "TimeModule.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Games/Game.h"

namespace GEngine
{
	GameModule::GameModule()
	{

	}

	void GameModule::Init(GEngineCoreModules* modules)
	{
		_modules = modules;
	}

	void GameModule::Tick() const
	{
		if (!_currentGame) return;

		const float deltaTime = _modules->time->GetDeltaTime();
		_currentGame->Tick(deltaTime);
	}

	void GameModule::Dispose()
	{
		if (!_currentGame) return;

		_currentGame->Dispose();
		_currentGame = nullptr;
	}

	void GameModule::LoadGame(const std::shared_ptr<Game> &game)
	{
		if (_currentGame != nullptr)
		{
			_currentGame->Dispose();
		}

		_modules->systems->RemoveAllSystemsNow();
		_modules->entities->RemoveAllEntitiesNow();

		_currentGame = game;

		_currentGame->Setup(_modules);
		_currentGame->Init();
	}
} // GEngineCore
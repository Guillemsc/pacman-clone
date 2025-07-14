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

	void GameModule::Init(const std::weak_ptr<GEngineCoreApplication> &app)
	{
		_app = app;
	}

	void GameModule::Tick() const
	{
		if (!_currentGame) return;

		const std::shared_ptr<GEngineCoreApplication> app = _app.lock();
		if (!app) return;

		const std::shared_ptr<TimeModule> time = app->Time().lock();
		if (!time) return;

		float deltaTime = time->GetDeltaTime();
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
		const std::shared_ptr<GEngineCoreApplication> app = _app.lock();
		if (!app) return;

		const std::shared_ptr<EntitiesModule> entities = app->Entities().lock();
		if (!entities) return;

		const std::shared_ptr<SystemsModule> systems = app->Systems().lock();
		if (!systems) return;

		if (_currentGame != nullptr)
		{
			_currentGame->Dispose();
		}

		systems->RemoveAllSystemsNow();
		entities->RemoveAllEntitiesNow();

		_currentGame = game;

		_currentGame->Setup(_app);
		_currentGame->Init();
	}
} // GEngineCore
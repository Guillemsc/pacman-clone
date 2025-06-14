//
// Created by guillem on 6/6/25.
//

#include "GEngineCoreApplication.h"

#include "Modules/ComponentsModule.h"
#include "Modules/EditorModule.h"
#include "Modules/EntitiesModule.h"
#include "Modules/GameModule.h"
#include "Modules/InputModule.h"
#include "Modules/RenderingModule.h"
#include "Modules/ResourcesModule.h"
#include "Modules/SystemsModule.h"
#include "Modules/WindowModule.h"
#include "spdlog/spdlog.h"

namespace GEngineCore
{
	GEngineCoreApplication::GEngineCoreApplication()
	{
		spdlog::info("Welcome to GEngineCore :)");

		_components = std::make_shared<ComponentsModule>();
		_entities = std::make_shared<EntitiesModule>();
		_game = std::make_shared<GameModule>();
		_window = std::make_shared<WindowModule>();
		_rendering = std::make_shared<RenderingModule>();
		_resources = std::make_shared<ResourcesModule>();
		_systems = std::make_shared<SystemsModule>();
		_input = std::make_shared<InputModule>();
		_editor = std::make_shared<EditorModule>();
	}

	GEngineCoreApplication::~GEngineCoreApplication()
	{
		spdlog::info("Bye :)");
	}

	void GEngineCoreApplication::Init()
	{
		spdlog::info("GEngineCore Init");

		_entities->Init(weak_from_this());
		_editor->Init(weak_from_this());
		_window->Init();
		_rendering->Init();
		_resources->Init();
		_systems->Init(weak_from_this());
		_game->Init(weak_from_this());
	}

	bool GEngineCoreApplication::CanRun() const
	{
		if (!_window->CanRun())
		{
			return false;
		}

		return true;
	}

	void GEngineCoreApplication::Tick() const
	{
		_game->Tick();
		_entities->Tick();
		_systems->Tick();
		_editor->Tick();
		_rendering->Tick();
		_window->Tick();
	}

	void GEngineCoreApplication::Dispose() const
	{
		spdlog::info("GEngineCore Dispose");

		_systems->Dispose();
		_game->Dispose();
		_entities->Dispose();
		_editor->Dispose();
		_resources->Dispose();
		_rendering->Dispose();
		_window->Dispose();
	}
} // GEngineCore
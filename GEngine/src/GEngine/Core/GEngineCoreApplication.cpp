//
// Created by guillem on 6/6/25.
//

#include "GEngineCoreApplication.h"

#include "GEngine/Modules/CameraModule.h"
#include "GEngine/Modules/CoroutinesModule.h"
#include "GEngine/Modules/EditorModule.h"
#include "GEngine/Modules/EntitiesModule.h"
#include "GEngine/Modules/ExamplesModule.h"
#include "GEngine/Modules/GameModule.h"
#include "GEngine/Modules/InputModule.h"
#include "GEngine/Modules/RenderingModule.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Modules/SystemsModule.h"
#include "GEngine/Modules/TimeModule.h"
#include "GEngine/Modules/UiModule.h"
#include "GEngine/Modules/WindowModule.h"
#include "spdlog/spdlog.h"

namespace GEngine
{
	GEngineCoreApplication::GEngineCoreApplication()
	{
		spdlog::info("Welcome to GEngineCore :)");

		_coroutines = std::make_shared<CoroutinesModule>();
		_entities = std::make_shared<EntitiesModule>();
		_game = std::make_shared<GameModule>();
		_camera = std::make_shared<CameraModule>();
		_window = std::make_shared<WindowModule>();
		_rendering = std::make_shared<RenderingModule>();
		_resources = std::make_shared<ResourcesModule>();
		_time = std::make_shared<TimeModule>();
		_systems = std::make_shared<SystemsModule>();
		_input = std::make_shared<InputModule>();
		_ui = std::make_shared<UiModule>();
		_editor = std::make_shared<EditorModule>();
		_examples = std::make_shared<ExamplesModule>();
	}

	GEngineCoreApplication::~GEngineCoreApplication()
	{
		spdlog::info("Bye :)");
	}

	void GEngineCoreApplication::Init()
	{
		spdlog::info("GEngineCore Init");

		_input->Init(weak_from_this());
		_entities->Init(weak_from_this());
		_editor->Init(weak_from_this());
		_window->Init(weak_from_this());
		_rendering->Init(weak_from_this());
		_resources->Init(weak_from_this());
		_camera->Init(weak_from_this());
		_ui->Init(weak_from_this());
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
		const float deltaTime = GetFrameTime();

		_ui->Tick();
		_game->Tick();
		_systems->Tick();
		_coroutines->Tick();
		_entities->Tick();
		_editor->Tick();
		_camera->Tick(deltaTime);
		_rendering->Tick();
		_window->Tick();
	}

	void GEngineCoreApplication::Dispose() const
	{
		spdlog::info("GEngineCore Dispose");

		_systems->Dispose();
		_game->Dispose();
		_entities->Dispose();
		_ui->Dispose();
		_editor->Dispose();
		_resources->Dispose();
		_rendering->Dispose();
		_window->Dispose();
	}
} // GEngineCore
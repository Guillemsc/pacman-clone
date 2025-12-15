//
// Created by guillem on 6/6/25.
//

#include "GEngineCoreApplication.h"

#include "GEngine/Memory/MemoryTracker.h"
#include "GEngine/Logging/GEngineLog.h"
#include "GEngine/Memory/MemoryTracker.h"
#include "GEngine/Modules/CameraModule.h"
#include "GEngine/Modules/Collisions2dModule.h"
#include "GEngine/Modules/ConfigurationModule.h"
#include "GEngine/Modules/CoroutinesModule.h"
#include "GEngine/Modules/DeferredExecutionModule.h"
#include "GEngine/Modules/EditorModule.h"
#include "GEngine/Modules/EntitiesModule.h"
#include "GEngine/Modules/ExamplesModule.h"
#include "GEngine/Modules/GameModule.h"
#include "GEngine/Modules/GuizmosModule.h"
#include "GEngine/Modules/InputModule.h"
#include "GEngine/Modules/RandomModule.h"
#include "GEngine/Modules/RenderingModule.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Modules/TickablesModule.h"
#include "GEngine/Modules/TimeModule.h"
#include "GEngine/Modules/TweensModule.h"
#include "GEngine/Modules/UiModule.h"
#include "GEngine/Modules/WindowModule.h"
#include "GEngine/Pooling/Pools.h"
#include "spdlog/spdlog.h"

namespace GEngine
{
	GEngineCoreApplication::GEngineCoreApplication()
	{
		GEngineLog::Init();

		MemoryTracker::Reset();

		GENGINE_INFO("Welcome to GEngine :)");

		Pools::Init();

		_configuration = std::make_unique<ConfigurationModule>();
		_entities = std::make_unique<EntitiesModule>();
		_game = std::make_unique<GameModule>();
		_camera = std::make_unique<CameraModule>();
		_window = std::make_unique<WindowModule>();
		_rendering = std::make_unique<RenderingModule>();
		_resources = std::make_unique<ResourcesModule>();
		_time = std::make_unique<TimeModule>();
		_tickables = std::make_unique<TickablesModule>();
		_input = std::make_unique<InputModule>();
		_tweens = std::make_unique<TweensModule>();
		_ui = std::make_unique<UiModule>();
		_coroutines = std::make_unique<CoroutinesModule>();
		_editor = std::make_unique<EditorModule>();
		_examples = std::make_unique<ExamplesModule>();
		_guizmos = std::make_unique<GuizmosModule>();
		_collisions2d = std::make_unique<Collisions2dModule>();
		_deferredExecution = std::make_unique<DeferredExecutionModule>();
		_random  = std::make_unique<RandomModule>();

		_modules = std::make_unique<GEngineCoreModules>(
			_configuration.get(),
			_entities.get(),
			_game.get(),
			_camera.get(),
			_window.get(),
			_rendering.get(),
			_resources.get(),
			_time.get(),
			_tickables.get(),
			_input.get(),
			_ui.get(),
			_coroutines.get(),
			_editor.get(),
			_examples.get(),
			_tweens.get(),
			_guizmos.get(),
			_collisions2d.get(),
			_deferredExecution.get(),
			_random.get()
		);
	}

	GEngineCoreApplication::~GEngineCoreApplication()
	{
	}

	void GEngineCoreApplication::Init() const
	{
		GENGINE_INFO("GEngine Init started.");

		_configuration->LoadConfiguration();
		_window->ApplyConfig(_configuration->GetConfig());

		_input->Init(_modules.get());
		_collisions2d->Init(_modules.get());
		_entities->Init(_modules.get());
		_coroutines->Init(_modules.get());
		_editor->Init(_modules.get());
		_window->Init(_modules.get());
		_rendering->Init(_modules.get());
		_resources->Init(_modules.get());
		_guizmos->Init(_modules.get());
		_camera->Init(_modules.get());
		_tweens->Init(_modules.get());
		_ui->Init(_modules.get());
		_game->Init(_modules.get());

		GENGINE_INFO("GEngine Init finished.");
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

		_tweens->Tick();
		_ui->Tick();
		_game->Tick();
		_tickables->Tick();
		_entities->Tick();
		_coroutines->Tick();
		_collisions2d->Tick();
		_deferredExecution->Tick();
		_editor->Tick();
		_camera->Tick(deltaTime);
		_rendering->Tick();
		_window->Tick();

		_entities->LateTick();
	}

	void GEngineCoreApplication::Dispose()
	{
		GENGINE_INFO("GEngine Dispose started.");

		_editor->Dispose();
		_tickables->Dispose();
		_game->Dispose();
		_entities->Dispose();
		_collisions2d->Dispose();
		_tweens->Dispose();
		_ui->Dispose();
		_deferredExecution->Dispose();
		_resources->Dispose();
		_coroutines->Dispose();
		_rendering->Dispose();
		_window->Dispose();

		_modules.reset();
		_configuration.reset();
		_entities.reset();
		_game.reset();
		_camera.reset();
		_window.reset();
		_rendering.reset();
		_resources.reset();
		_time.reset();
		_tickables.reset();
		_input.reset();
		_ui.reset();
		_editor.reset();
		_coroutines.reset();
		_examples.reset();
		_tweens.reset();
		_guizmos.reset();
		_collisions2d.reset();
		_deferredExecution.reset();
		_random.reset();

		Pools::Dispose();

		GENGINE_INFO("GEngine Dispose finished.");
		GENGINE_INFO("Bye :)");

		MemoryTracker::LogLeaks();

		GEngineLog::Dispose();
	}
} // GEngineCore
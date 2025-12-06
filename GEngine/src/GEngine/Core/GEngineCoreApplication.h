//
// Created by guillem on 6/6/25.
//

#ifndef GENGINECOREAPPLICATION_H
#define GENGINECOREAPPLICATION_H

#include <memory>

#include "GEngineCoreModules.h"
#include "GEngine/Core/GEngineCoreApplication.h"

namespace GEngine
{
	class TimeModule;
	class ExamplesModule;
	class UiModule;
	class CameraModule;
	class EditorModule;
	class RenderingModule;
	class GameModule;
	class ComponentsModule;
	class EntitiesModule;
	class WindowModule;
	class TickablesModule;
	class ResourcesModule;
	class InputModule;
	class EventBuses;

	class GEngineCoreApplication : public std::enable_shared_from_this<GEngineCoreApplication>
	{
	public:
		GEngineCoreApplication();
		~GEngineCoreApplication();

		void Init() const;
		bool CanRun() const;
		void Tick() const;
		void Dispose() const;

		GEngineCoreModules* Modules() const { return _modules.get(); }

	private:
		std::unique_ptr<ConfigurationModule> _configuration;
		std::unique_ptr<EntitiesModule> _entities;
		std::unique_ptr<GameModule> _game;
		std::unique_ptr<CameraModule> _camera;
		std::unique_ptr<WindowModule> _window;
		std::unique_ptr<RenderingModule> _rendering;
		std::unique_ptr<ResourcesModule> _resources;
		std::unique_ptr<TimeModule> _time;
		std::unique_ptr<TickablesModule> _tickables;
		std::unique_ptr<InputModule> _input;
		std::unique_ptr<UiModule> _ui;
		std::unique_ptr<EditorModule> _editor;
		std::unique_ptr<CoroutinesModule> _coroutines;
		std::unique_ptr<ExamplesModule> _examples;
		std::unique_ptr<TweensModule> _tweens;
		std::unique_ptr<GuizmosModule> _guizmos;
		std::unique_ptr<Collisions2dModule> _collisions2d;

		std::unique_ptr<GEngineCoreModules> _modules;
	};
} // GEngineCore

#endif //GENGINECOREAPPLICATION_H

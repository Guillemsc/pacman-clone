//
// Created by guillem on 6/6/25.
//

#ifndef GENGINECOREAPPLICATION_H
#define GENGINECOREAPPLICATION_H

#include <memory>

#include "GEngine/Core/GEngineCoreApplication.h"

namespace GEngine
{
	class TimeModule;
	class ExamplesModule;
	class UiModule;
	class CoroutinesModule;
	class CameraModule;
	class EditorModule;
	class RenderingModule;
	class GameModule;
	class ComponentsModule;
	class EntitiesModule;
	class WindowModule;
	class SystemsModule;
	class ResourcesModule;
	class InputModule;
	class EventBuses;

	class GEngineCoreApplication : public std::enable_shared_from_this<GEngineCoreApplication>
	{
	public:
		GEngineCoreApplication();
		~GEngineCoreApplication();

		void Init();
		bool CanRun() const;
		void Tick() const;
		void Dispose() const;

		std::weak_ptr<EntitiesModule> Entities() { return _entities; }
		std::weak_ptr<GameModule> Game() { return _game; }
		std::weak_ptr<CameraModule> Camera() { return _camera; }
		std::weak_ptr<WindowModule> Window() { return _window; }
		std::weak_ptr<RenderingModule> Rendering() { return _rendering; }
		std::weak_ptr<ResourcesModule> Resources() { return _resources; }
		std::weak_ptr<SystemsModule> Systems() { return _systems; }
		std::weak_ptr<TimeModule> Time() { return _time; }
		std::weak_ptr<InputModule> Input() { return _input; }
		std::weak_ptr<UiModule> Ui() { return _ui; }
		std::weak_ptr<CoroutinesModule> Coroutines() { return _coroutines; }
		std::weak_ptr<EditorModule> Editor() { return _editor; }
		std::weak_ptr<ExamplesModule> Examples() { return _examples; }

	private:
		std::shared_ptr<EntitiesModule> _entities;
		std::shared_ptr<GameModule> _game;
		std::shared_ptr<CameraModule> _camera;
		std::shared_ptr<WindowModule> _window;
		std::shared_ptr<RenderingModule> _rendering;
		std::shared_ptr<ResourcesModule> _resources;
		std::shared_ptr<TimeModule> _time;
		std::shared_ptr<SystemsModule> _systems;
		std::shared_ptr<InputModule> _input;
		std::shared_ptr<UiModule> _ui;
		std::shared_ptr<CoroutinesModule> _coroutines;
		std::shared_ptr<EditorModule> _editor;
		std::shared_ptr<ExamplesModule> _examples;
	};
} // GEngineCore

#endif //GENGINECOREAPPLICATION_H

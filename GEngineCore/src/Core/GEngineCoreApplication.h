//
// Created by guillem on 6/6/25.
//

#ifndef GENGINECOREAPPLICATION_H
#define GENGINECOREAPPLICATION_H

#include <memory>

#include "Core/GEngineCoreApplication.h"
#include "Modules/ResourcesModule.h"

namespace GEngineCore
{
	class EditorModule;
	class RenderingModule;
	class GameModule;
	class ComponentsModule;
	class EntitiesModule;
	class WindowModule;
	class SystemsModule;
	class EventBuses;

	class GEngineCoreApplication : public std::enable_shared_from_this<GEngineCoreApplication>
	{
	public:
		GEngineCoreApplication();
		~GEngineCoreApplication();

		void Init();
		bool CanRun() const;
		void Tick();
		void Dispose() const;

		std::weak_ptr<ComponentsModule> Components() { return _components; }
		std::weak_ptr<EntitiesModule> Entities() { return _entities; }
		std::weak_ptr<GameModule> Game() { return _game; }
		std::weak_ptr<WindowModule> Window() { return _window; }
		std::weak_ptr<RenderingModule> Rendering() { return _rendering; }
		std::weak_ptr<ResourcesModule> Resources() { return _resources; }
		std::weak_ptr<SystemsModule> Systems() { return _systems; }
		std::weak_ptr<EditorModule> Editor() { return _editor; }

	private:
		std::shared_ptr<ComponentsModule> _components = nullptr;
		std::shared_ptr<EntitiesModule> _entities = nullptr;
		std::shared_ptr<GameModule> _game = nullptr;
		std::shared_ptr<WindowModule> _window = nullptr;
		std::shared_ptr<RenderingModule> _rendering = nullptr;
		std::shared_ptr<ResourcesModule> _resources = nullptr;
		std::shared_ptr<SystemsModule> _systems = nullptr;
		std::shared_ptr<EditorModule> _editor = nullptr;
	};
} // GEngineCore

#endif //GENGINECOREAPPLICATION_H

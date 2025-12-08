//
// Created by guillem on 6/30/25.
//

#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>

#include "tokoro.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Scenes/Scene.h"

namespace GEngine
{
	class CoroutinesRunner;
}

namespace GEngine
{
	class EntitiesModule;
	class Entity;
}

namespace PacMan
{
	class Context
	{
	public:
		explicit Context(GEngine::GEngineCoreModules* modules, const std::string& name);
		virtual ~Context() = default;

		tokoro::Async<void> LoadAsync();
		void Start();
		void Dispose();

		GEngine::CoroutinesRunner* GetCoroutinesRunner() const;

	protected:
		virtual tokoro::Async<void> OnLoadAsync();
		virtual void OnStart();
		virtual void OnDispose();

	protected:
		GEngine::GEngineCoreModules* const _modules;
		std::unique_ptr<GEngine::Scene> _scene;

	private:
		const std::string _name;
		std::weak_ptr<GEngine::CoroutinesRunner> _coroutineRunner;

		bool _loaded = false;
		bool _started = false;
		bool _disposed = false;
	};
}

#endif //CONTEXT_H

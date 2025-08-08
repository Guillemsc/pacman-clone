//
// Created by guillem on 6/30/25.
//

#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>

#include "tokoro.h"
#include "GEngine/Coroutines/Coroutine.h"
#include "GEngine/Scenes/Scene.h"

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
		explicit Context(const std::string& name);

		tokoro::Async<void> LoadAsync();
		void Start();
		void Dispose();

		GEngine::Scene GetScene() const;

	protected:
		virtual tokoro::Async<void> OnLoadAsync();
		virtual void OnStart();
		virtual void OnDispose();

	private:
		std::string _name;
		bool _loaded = false;
		bool _started = false;
		bool _disposed = false;

		GEngine::Scene _scene;
	};
}

#endif //CONTEXT_H

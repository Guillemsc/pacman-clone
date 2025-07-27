//
// Created by guillem on 6/30/25.
//

#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>

#include "tokoro.h"
#include "GEngine/Coroutines/Coroutine.h"

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

		std::weak_ptr<GEngine::Entity> AddWorldEntity() const;
		std::weak_ptr<GEngine::Entity> AddUiEntity() const;

	protected:
		virtual tokoro::Async<void> OnLoadAsync();
		virtual void OnStart();
		virtual void OnDispose();

	private:
		std::string _name;
		bool _loaded = false;
		bool _started = false;
		bool _disposed = false;

	private:
		std::weak_ptr<GEngine::EntitiesModule> _entities;

		std::weak_ptr<GEngine::Entity> _rootUiEntity;
		std::weak_ptr<GEngine::Entity> _rootWorldEntity;
	};
}

#endif //CONTEXT_H

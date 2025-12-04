//
// Created by guillem on 6/30/25.
//

#include "Context.h"

#include <format>

#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Modules/CoroutinesModule.h"
#include "GEngine/Modules/EntitiesModule.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"

namespace PacMan
{
	Context::Context(GEngine::GEngineCoreModules* modules, const std::string &name)
		: _modules(modules), _name(name)
	{
		_scene = std::make_unique<GEngine::Scene>(modules->entities, name);
		_coroutineRunner = modules->coroutines->CreateRunner();
	}

	tokoro::Async<void> Context::LoadAsync()
	{
		if (_loaded) co_return;

		_disposed = false;
		_started = false;
		_loaded = true;

		co_await OnLoadAsync();
	}

	void Context::Start()
	{
		if (!_loaded) return;
		if (_started) return;

		_started = true;

		OnStart();
	}

	void Context::Dispose()
	{
		if (!_loaded) return;
		if (_disposed) return;

		_loaded = false;
		_disposed = true;

		OnDispose();

		_modules->coroutines->DestroyRunner(_coroutineRunner);

		_scene->Dispose();
	}

	GEngine::CoroutinesRunner* Context::GetCoroutinesRunner() const
	{
		return _coroutineRunner.lock().get();
	}

	tokoro::Async<void> Context::OnLoadAsync()
	{
		co_return;
	}

	void Context::OnStart()
	{
	}

	void Context::OnDispose()
	{

	}
}

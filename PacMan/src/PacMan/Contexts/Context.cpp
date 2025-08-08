//
// Created by guillem on 6/30/25.
//

#include "Context.h"

#include <format>

#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Coroutines/CoroutineBuilder.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Modules/EntitiesModule.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"

namespace PacMan
{
	Context::Context(const std::string &name)
	{
		_name = name;
	}

	tokoro::Async<void> Context::LoadAsync()
	{
		if (_loaded) co_return;

		_disposed = false;
		_started = false;
		_loaded = true;

		const std::shared_ptr<GEngine::GEngineCoreApplication> app = GEngine::ServiceLocator::Get<GEngine::GEngineCoreApplication>();
		if (!app) co_return;

		_scene.Init(app->Entities(), _name);

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

		_scene.Dispose();
	}

	GEngine::Scene Context::GetScene() const
	{
		return _scene;
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

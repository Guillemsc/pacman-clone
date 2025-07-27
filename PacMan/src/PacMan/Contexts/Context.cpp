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

		const auto app = GEngine::ServiceLocator::Get<GEngine::GEngineCoreApplication>();
		if (!app) co_return;

		_entities = app->Entities();

		_rootUiEntity = _entities.lock()->AddUiEntity();
		_rootUiEntity.lock()->SetName(std::format("{0} Ui", _name));

		_rootWorldEntity = _entities.lock()->AddWorldEntity();
		_rootWorldEntity.lock()->SetName(std::format("{0} World", _name));

		co_await OnLoadAsync();
	}

	std::weak_ptr<GEngine::Entity> Context::AddWorldEntity() const
	{
		return _entities.lock()->AddWorldEntity(_rootWorldEntity);
	}

	std::weak_ptr<GEngine::Entity> Context::AddUiEntity() const
	{
		return _entities.lock()->AddUiEntity(_rootUiEntity);
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

		const auto app = GEngine::ServiceLocator::Get<GEngine::GEngineCoreApplication>();
		if (!app) return;

		const std::shared_ptr<GEngine::EntitiesModule> entities = app->Entities().lock();
		entities->RemoveEntity(_rootUiEntity);
		entities->RemoveEntity(_rootWorldEntity);
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

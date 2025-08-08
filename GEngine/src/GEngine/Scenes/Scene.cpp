//
// Created by guillem on 8/7/25.
//

#include "Scene.h"

#include <format>

#include "GEngine/Entities/Entity.h"
#include "GEngine/Modules/EntitiesModule.h"

namespace GEngine
{
	void Scene::Init(const std::weak_ptr<EntitiesModule> &entitiesPtr, const std::string& name)
	{
		_entitiesPtr = entitiesPtr;

		const std::shared_ptr<EntitiesModule> entities = _entitiesPtr.lock();
		if (!entities) return;

		_rootUiEntity = entities->AddUiEntity();
		_rootUiEntity.lock()->SetName(std::format("{0} Ui", name));

		_rootWorldEntity = entities->AddWorldEntity();
		_rootWorldEntity.lock()->SetName(std::format("{0} World", name));
	}

	void Scene::Dispose() const
	{
		const std::shared_ptr<EntitiesModule> entities = _entitiesPtr.lock();
		if (!entities) return;

		entities->RemoveEntity(_rootUiEntity);
		entities->RemoveEntity(_rootWorldEntity);
	}

	std::weak_ptr<Entity> Scene::AddWorldEntity() const
	{
		const std::shared_ptr<EntitiesModule> entities = _entitiesPtr.lock();
		if (!entities) return std::weak_ptr<Entity>();

		if (_rootWorldEntity.expired()) return std::weak_ptr<Entity>();

		return entities->AddWorldEntity(_rootWorldEntity);
	}

	std::weak_ptr<Entity> Scene::AddUiEntity() const
	{
		const std::shared_ptr<EntitiesModule> entities = _entitiesPtr.lock();
		if (!entities) return std::weak_ptr<Entity>();

		if (_rootUiEntity.expired()) return std::weak_ptr<Entity>();

		return entities->AddUiEntity(_rootWorldEntity);
	}
} // GEngine
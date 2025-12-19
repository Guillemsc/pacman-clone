//
// Created by guillem on 8/7/25.
//

#include "Scene.h"

#include <format>

#include "GEngine/Entities/Entity.h"
#include "GEngine/Modules/EntitiesModule.h"

namespace GEngine
{
	Scene::Scene(EntitiesModule *entitiesModule, const std::string &name)
		: _entitiesModule(entitiesModule)
	{
		_rootUiEntity = _entitiesModule->AddUiEntity();
		_rootUiEntity.lock()->SetName(std::format("{0} Ui", name));

		_rootWorldEntity = _entitiesModule->AddWorldEntity();
		_rootWorldEntity.lock()->SetName(std::format("{0} World", name));
	}

	void Scene::Dispose() const
	{
		_entitiesModule->RemoveEntity(_rootUiEntity);
		_entitiesModule->RemoveEntity(_rootWorldEntity);
	}

	std::weak_ptr<Entity> Scene::AddWorldEntity() const
	{
		if (_rootWorldEntity.expired()) return std::weak_ptr<Entity>();

		return _entitiesModule->AddWorldEntity(_rootWorldEntity);
	}

	std::weak_ptr<Entity> Scene::AddUiEntity() const
	{
		if (_rootUiEntity.expired()) return std::weak_ptr<Entity>();

		return _entitiesModule->AddUiEntity(_rootUiEntity);
	}

	bool Scene::RemoveEntity(const std::weak_ptr<Entity> &entity) const
	{
		return _entitiesModule->RemoveEntity(entity);
	}
} // GEngine
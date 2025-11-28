//
// Created by guillem on 8/7/25.
//

#include "Scene.h"

#include <format>

#include "GEngine/Entities/Entity.h"
#include "GEngine/Modules/EntitiesModule.h"

namespace GEngine
{
	Scene::Scene(EntitiesModule *entitiesPtr, const std::string &name)
		: _entitiesPtr(entitiesPtr)
	{
		_rootUiEntity = _entitiesPtr->AddUiEntity();
		_rootUiEntity.lock()->SetName(std::format("{0} Ui", name));

		_rootWorldEntity = _entitiesPtr->AddWorldEntity();
		_rootWorldEntity.lock()->SetName(std::format("{0} World", name));
	}

	void Scene::Dispose() const
	{
		_entitiesPtr->RemoveEntity(_rootUiEntity);
		_entitiesPtr->RemoveEntity(_rootWorldEntity);
	}

	std::weak_ptr<Entity> Scene::AddWorldEntity() const
	{
		if (_rootWorldEntity.expired()) return std::weak_ptr<Entity>();

		return _entitiesPtr->AddWorldEntity(_rootWorldEntity);
	}

	std::weak_ptr<Entity> Scene::AddUiEntity() const
	{
		if (_rootUiEntity.expired()) return std::weak_ptr<Entity>();

		return _entitiesPtr->AddUiEntity(_rootWorldEntity);
	}
} // GEngine
//
// Created by guillem on 8/7/25.
//

#include "Scene.h"

#include <format>

#include "GEngine/Components/UiTransformComponent.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Modules/EntitiesModule.h"

namespace GEngine
{
	Scene::Scene(EntitiesModule *entitiesModule, const std::string &name)
		: _entitiesModule(entitiesModule)
	{
		const std::shared_ptr<Entity> rootUi = _entitiesModule->AddUiEntity().lock();
		rootUi->SetName(std::format("{0} Ui", name));
		rootUi->GetUiTransform().lock()->ExpandOnParent();
		_rootUiEntity = rootUi;

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
		return AddUiEntity(_rootUiEntity);
	}

	std::weak_ptr<Entity> Scene::AddUiEntity(const std::weak_ptr<Entity> &parent) const
	{
		if (_rootUiEntity.expired()) return std::weak_ptr<Entity>();

		return _entitiesModule->AddUiEntity(parent);
	}

	bool Scene::RemoveEntity(const std::weak_ptr<Entity> &entity) const
	{
		return _entitiesModule->RemoveEntity(entity);
	}
} // GEngine
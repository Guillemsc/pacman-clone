//
// Created by guillem on 6/7/25.
//

#include "ComponentsModule.h"

#include "GEngine/Components/CameraComponent.h"
#include "GEngine/Components/Shape2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Components/Texture2dRendererComponent.h"
#include "GEngine/Components/TiledMap2dRendererComponent.h"

namespace GEngine
{
	ComponentsModule::ComponentsModule()
	{

	}

	void ComponentsModule::Dispose()
	{
		_componentFactories.clear();
	}

	bool ComponentsModule::RemoveComponentFromEntity(
		const std::weak_ptr<Entity> &entityPtr,
		const std::weak_ptr<Component> &componentPtr
		)
	{
		const std::shared_ptr<Entity> entity = entityPtr.lock();
		if (entity == nullptr) return false;

		const std::shared_ptr<Component> component = componentPtr.lock();
		if (component == nullptr) return false;

		for (auto it = entity->_components.begin(); it != entity->_components.end(); ++it)
		{
			if (it->get() == component.get())
			{
				(*it)->OnDestroy();
				entity->_components.erase(it);
				return true;
			}
		}

		return false;
	}

	void ComponentsModule::RemoveAllComponentsFromEntity(const std::weak_ptr<Entity> &entityPtr)
	{
		const std::shared_ptr<Entity> entity = entityPtr.lock();
		if (entity == nullptr) return;

		for (auto it = entity->_components.begin(); it != entity->_components.end(); ++it)
		{
			(*it)->SetEnabled(false);
			(*it)->OnDestroy();
		}

		entity->_components.clear();
	}

	void ComponentsModule::TickEntityComponents(Entity* entityPtr)
	{
		for (auto it = entityPtr->_components.begin(); it != entityPtr->_components.end(); ++it)
		{
			if (!(*it)->_isEnabledInHierarchy)
			{
				continue;
			}

			(*it)->OnTick();
		}
	}
} // GEngineCore
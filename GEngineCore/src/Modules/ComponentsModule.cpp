//
// Created by guillem on 6/7/25.
//

#include "ComponentsModule.h"

#include "Components/ShapeRenderer2dComponent.h"
#include "Components/TransformComponent.h"
#include "Components/ComponentFactory.h"

namespace GEngineCore
{
	ComponentsModule::ComponentsModule()
	{
		RegisterComponent<TransformComponent>(false);
		RegisterComponent<ShapeRenderer2dComponent>(false);
	}

	void ComponentsModule::Dispose()
	{
		_componentFactories.clear();
	}

	std::weak_ptr<Component> ComponentsModule::AddEntityComponent(const std::weak_ptr<Entity> &entityPtr, const ComponentType componentType)
	{
		const std::shared_ptr<Entity> entity = entityPtr.lock();
		if (entity == nullptr) return std::weak_ptr<Component>();

		const std::weak_ptr<IComponentFactory> componentFactoryPtr = GetComponentFactory(componentType);

		const std::shared_ptr<IComponentFactory> componentFactory = componentFactoryPtr.lock();
		if (!componentFactory) return std::weak_ptr<Component>();

		if (!componentFactory->GetAllowMultiple())
		{
			const bool alreadyExists = entity->GetComponent(componentType).lock() != nullptr;

			if (alreadyExists)
			{
				return std::weak_ptr<Component>();
			}
		}

		const std::shared_ptr<Component> component = componentFactory->CreateComponent(entityPtr);
		if (!component) return std::weak_ptr<Component>();

		entity->_components.push_back(component);

		return component;
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

	bool ComponentsModule::RemoveComponentFromEntity(
		const std::weak_ptr<Entity> &entityPtr,
		ComponentType componentType
		)
	{
		const std::shared_ptr<Entity> entity = entityPtr.lock();
		if (entity == nullptr) return false;

		for (auto it = entity->_components.begin(); it != entity->_components.end(); ++it)
		{
			if ((*it)->GetType() == componentType)
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
			(*it)->OnDestroy();
		}

		entity->_components.clear();
	}

	std::weak_ptr<IComponentFactory> ComponentsModule::GetComponentFactory(ComponentType componentType)
	{
		const std::size_t componentIndex = static_cast<std::size_t>(componentType);

		if (_componentFactories.size() <= componentIndex)
		{
			return std::weak_ptr<IComponentFactory>();
		}

		return _componentFactories[componentIndex];
	}

	void ComponentsModule::TickEntityComponents(const std::weak_ptr<Entity> &entityPtr)
	{
		const std::shared_ptr<Entity> entity = entityPtr.lock();
		if (entity == nullptr) return;

		for (auto it = entity->_components.begin(); it != entity->_components.end(); ++it)
		{
			(*it)->OnTick();
		}
	}
} // GEngineCore
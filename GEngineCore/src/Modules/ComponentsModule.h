//
// Created by guillem on 6/7/25.
//

#ifndef COMPONENTSMODULE_H
#define COMPONENTSMODULE_H

#include <vector>

#include "Components/ComponentFactory.h"
#include "Components/ComponentType.h"

namespace GEngineCore
{
	class IComponentFactory;
	class ComponentRef;
	class TransformComponent;
	class Component;
	class Entity;

	class ComponentsModule
	{
		friend class EntitiesModule;

	public:
		ComponentsModule();

		void Dispose();

		template <class T>
		std::weak_ptr<T> AddEntityComponent(const std::weak_ptr<Entity> &entityPtr);
		std::weak_ptr<Component> AddEntityComponent(const std::weak_ptr<Entity> &entityPtr, ComponentType componentType);
		bool RemoveComponentFromEntity(const std::weak_ptr<Entity> &entityPtr, const std::weak_ptr<Component> &componentPtr);
		bool RemoveComponentFromEntity(const std::weak_ptr<Entity> &entityPtr, ComponentType componentType);
		void RemoveAllComponentsFromEntity(const std::weak_ptr<Entity> &entityPtr);

	private:
		template <class T>
		std::weak_ptr<ComponentFactory<T>> GetComponentFactory();
		std::weak_ptr<IComponentFactory> GetComponentFactory(ComponentType componentType);
		void TickEntityComponents(Entity* entityPtr);

		template <class T>
		void RegisterComponent(bool allowMultiple);

	private:
		std::vector<std::shared_ptr<IComponentFactory>> _componentFactories;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class T>
	std::weak_ptr<T> ComponentsModule::AddEntityComponent(const std::weak_ptr<Entity> &entityPtr)
	{
		static_assert(std::is_base_of_v<Component, T>, "T is not derived from Component");
		const ComponentType componentType = T::GetTypeStatic();

		const std::weak_ptr<Component> componentPtr = AddEntityComponent(entityPtr, componentType);

		const std::shared_ptr<Component> component = componentPtr.lock();
		if (!component) return std::weak_ptr<T>();

		std::shared_ptr<T> castedComponent = std::static_pointer_cast<T>(component);
		if (!castedComponent) return std::weak_ptr<T>();

		return castedComponent;
	}

	template<class T>
	std::weak_ptr<ComponentFactory<T>> ComponentsModule::GetComponentFactory()
	{
		static_assert(std::is_base_of_v<Component, T>, "T is not derived from Component");

		const ComponentType componentType = T::GetType();

		std::weak_ptr<IComponentFactory> componentFactoryPtr = GetComponentFactory(componentType);

		const std::shared_ptr<IComponentFactory> componentFactory = componentFactoryPtr.lock();
		if (!componentFactory) return std::weak_ptr<T>();

		const std::shared_ptr<ComponentFactory<T>> derivedComponentFactory = std::dynamic_pointer_cast<ComponentFactory<T>>(componentFactory);

		if (derivedComponentFactory == nullptr)
		{
			return std::weak_ptr<ComponentFactory<T>>();
		}

		return derivedComponentFactory;
	}

	template <class T>
	void ComponentsModule::RegisterComponent(bool allowMultiple)
	{
		static_assert(std::is_base_of_v<Component, T>, "T is not derived from Component");

		const ComponentType componentType = T::GetTypeStatic();
		const std::size_t componentIndex = static_cast<std::size_t>(componentType);

		while (componentIndex + 1 > _componentFactories.size())
		{
			_componentFactories.push_back(nullptr);
		}

		_componentFactories[componentIndex] = std::make_shared<ComponentFactory<T>>(allowMultiple);
	}
}

#endif //COMPONENTSMODULE_H

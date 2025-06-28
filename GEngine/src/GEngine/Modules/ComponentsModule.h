//
// Created by guillem on 6/7/25.
//

#ifndef COMPONENTSMODULE_H
#define COMPONENTSMODULE_H

#include <memory>
#include <vector>

namespace GEngine
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

		bool RemoveComponentFromEntity(const std::weak_ptr<Entity> &entityPtr, const std::weak_ptr<Component> &componentPtr);
		void RemoveAllComponentsFromEntity(const std::weak_ptr<Entity> &entityPtr);

	private:
		void TickEntityComponents(Entity* entityPtr);

	private:
		std::vector<std::shared_ptr<IComponentFactory>> _componentFactories;
	};
}

#endif //COMPONENTSMODULE_H

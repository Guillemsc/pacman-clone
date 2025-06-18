//
// Created by guillem on 6/6/25.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <functional>
#include <memory>
#include <vector>

#include "Core/GEngineCoreApplication.h"
#include "Components/ComponentType.h"
#include "Modules/ComponentsModule.h"
#include "Objects/GEngineObject.h"

namespace GEngineCore
{
	class Component;
	class TransformComponent;
}

namespace GEngineCore
{
	class GEngineCoreApplication;

	class Entity final : public GEngineObject, public std::enable_shared_from_this<Entity>
	{
		friend class EntitiesModule;
		friend class ComponentsModule;

	public:
		explicit Entity(const std::weak_ptr<GEngineCoreApplication>& appPtr, std::uint32_t id);
		~Entity() override;

		static GEngineObjectType GetObjectTypeStatic() { return GEngineObjectType::ENTITY; }
		GEngineObjectType GetObjectType() override { return GetObjectTypeStatic(); }

		std::weak_ptr<GEngineCoreApplication> GetApp() const;
		std::uint32_t GetId() const;

		void SetName(const std::string& name);
		std::string GetName() const;

		bool IsActiveSelf() const;
		bool IsActiveInHierarchy() const;
		void SetActive(bool active);

		bool IsInsideChildHierarchy(const std::weak_ptr<Entity> &checkingPtr) const;
		void SetParent(const std::weak_ptr<Entity> &parentPtr, bool worldPositionStays = true);
		void RemoveParent(bool worldPositionStays = true);
		void ForEachEntityInChildHierarchy(bool includeCurrent, const std::function<bool(const std::shared_ptr<Entity>&)> &callback);

		std::weak_ptr<Entity> GetParent() const;
		const std::vector<std::weak_ptr<Entity>>& GetChildren() const;

		const std::vector<std::shared_ptr<Component>>& GetComponents() const;
		std::weak_ptr<Component> GetComponent(ComponentType componentType);
		template <class T>
		std::weak_ptr<T> GetComponent();
		std::weak_ptr<Component> AddComponent(ComponentType componentType);
		template <class T>
		std::weak_ptr<T> AddComponent();

		std::weak_ptr<TransformComponent> GetTransform() const;

	private:
		void Dispose();

		void RefreshChildrenHierarchyActiveState();
		bool RefreshActiveState();

	private:
		std::weak_ptr<GEngineCoreApplication> _appPtr;
		std::uint32_t _id = 0;
		std::string _name;

		bool _isAlive = true;
		bool _isActiveSelf = false;
		bool _isActiveInHierarchy = false;

		std::weak_ptr<Entity> _parentPtr;
		std::vector<std::weak_ptr<Entity>> _childEntities;

		std::vector<std::shared_ptr<Component>> _components;
		std::weak_ptr<TransformComponent> _transformPtr;
	};

	template<class T>
	std::weak_ptr<T> Entity::GetComponent()
	{
		static_assert(std::is_base_of_v<Component, T>, "T is not derived from Component");
		const ComponentType componentType = T::GetTypeStatic();

		const std::weak_ptr<Component> componentPtr = GetComponent(componentType);

		const std::shared_ptr<Component> component = componentPtr.lock();
		if (!component) return std::weak_ptr<T>();

		return std::static_pointer_cast<T>(component);
	}

	template<class T>
	std::weak_ptr<T> Entity::AddComponent()
	{
		const std::shared_ptr<GEngineCoreApplication> app = _appPtr.lock();
		if (app == nullptr) return std::weak_ptr<T>();

		const std::shared_ptr<ComponentsModule> components = app->Components().lock();
		if (components == nullptr) return std::weak_ptr<T>();

		return components->AddEntityComponent<T>(weak_from_this());
	}
}


#endif //ENTITY_H

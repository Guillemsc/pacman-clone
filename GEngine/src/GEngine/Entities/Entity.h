//
// Created by guillem on 6/6/25.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <functional>
#include <memory>
#include <vector>

#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Objects/GEngineObject.h"

namespace GEngine
{
	class UiTransformComponent;
	class Component;
	class TransformComponent;
}

namespace GEngine
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
		template <class T>
		std::weak_ptr<T> GetComponent();
		template <class T>
		std::weak_ptr<T> AddComponent();
		bool RemoveComponent(const std::weak_ptr<Component> &componentPtr);

		std::weak_ptr<TransformComponent> GetTransform() const;
		std::weak_ptr<UiTransformComponent> GetUiTransform() const;

	private:
		void Dispose();

		void TickAllComponents();
		void RemoveAllComponents();

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

		std::vector<std::shared_ptr<Component>> _components; // TODO: Make contiguous arrays of Components, this is faster to impl for now :)
		std::weak_ptr<TransformComponent> _transformPtr;
		std::weak_ptr<UiTransformComponent> _uiTransformPtr;
	};

	template<class T>
	std::weak_ptr<T> Entity::GetComponent()
	{
		for (auto it = _components.begin(); it != _components.end(); ++it)
		{
			if (auto casted = std::dynamic_pointer_cast<T>(*it))
			{
				return casted;
			}
		}

		return std::weak_ptr<T>();
	}

	template<class T>
	std::weak_ptr<T> Entity::AddComponent()
	{
		static_assert(std::is_base_of_v<Component, T>, "T is not derived from Component");

		const std::shared_ptr<GEngineCoreApplication> app = _appPtr.lock();
		if (app == nullptr) return std::weak_ptr<T>();

		const std::shared_ptr<T> component = std::make_shared<T>(weak_from_this());

		if (_transformPtr.expired())
		{
			if constexpr (std::is_same_v<T, TransformComponent>)
			{
				_transformPtr = component;
			}
		}

		if (_uiTransformPtr.expired())
		{
			if constexpr (std::is_same_v<T, UiTransformComponent>)
			{
				_uiTransformPtr = component;
			}
		}

		_components.push_back(component);

		component->SetEnabled(true);

		return component;
	}
}


#endif //ENTITY_H

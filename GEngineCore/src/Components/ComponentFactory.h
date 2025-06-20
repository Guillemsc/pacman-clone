//
// Created by guillem on 6/8/25.
//

#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <memory>

#include "ComponentType.h"

namespace GEngineCore
{
	class Component;
	class Entity;
}

namespace GEngineCore
{
	class IComponentFactory
	{
	public:
		virtual ~IComponentFactory() = default;

		virtual bool GetAllowMultiple() = 0;
		virtual std::shared_ptr<Component> CreateComponent(const std::weak_ptr<Entity> &entityPtr) = 0;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template <class T>
	class ComponentFactory final : public IComponentFactory
	{
	public:
		explicit ComponentFactory(bool allowMultiple);
		bool GetAllowMultiple() override;
		std::shared_ptr<Component> CreateComponent(const std::weak_ptr<Entity> &entityPtr) override;

	private:
		bool _allowMultiple;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class T>
	ComponentFactory<T>::ComponentFactory(const bool allowMultiple)
	{
		_allowMultiple = allowMultiple;
	}

	template<class T>
	bool ComponentFactory<T>::GetAllowMultiple()
	{
		return _allowMultiple;
	}

	template<class T>
	std::shared_ptr<Component> ComponentFactory<T>::CreateComponent(const std::weak_ptr<Entity> &entityPtr)
	{
		return std::make_shared<T>(entityPtr);
	}

	// -------------------------------------------------------
	// -------------------------------------------------------
}

#endif //COMPONENTFACTORY_H

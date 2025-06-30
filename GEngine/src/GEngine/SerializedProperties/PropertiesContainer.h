//
// Created by guillem on 6/29/25.
//

#ifndef PROPERTIESCONTAINER_H
#define PROPERTIESCONTAINER_H

#include <memory>
#include <vector>

#include "Property.h"

namespace GEngine
{
	class GEngineObject;

	class PropertiesContainer
	{
	public:
		template<class T>
		std::shared_ptr<Property<T>> Register(const std::string& name, T value);
		template<class T>
		std::shared_ptr<Property<std::shared_ptr<T>>> RegisterObject(const std::string& name, std::shared_ptr<T> value);

		const std::vector<std::shared_ptr<IProperty>>& GetProperties() const;

	private:
		std::vector<std::shared_ptr<IProperty>> _properties;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class T>
	std::shared_ptr<Property<T>> PropertiesContainer::Register(const std::string& name, T value)
	{
		std::shared_ptr<Property<T>> property = std::make_shared<Property<T>>(name, value);
		_properties.push_back(property);
		return property;
	}

	template<class T>
	std::shared_ptr<Property<std::shared_ptr<T>>> PropertiesContainer::RegisterObject(const std::string &name, std::shared_ptr<T> value)
	{
		static_assert(std::is_base_of_v<GEngineObject, T>, "T must derive from GEngineObject");
		std::shared_ptr<Property<std::shared_ptr<T>>> property = std::make_shared<Property<std::shared_ptr<T>>>(name, value);
		return property;
	}

	inline const std::vector<std::shared_ptr<IProperty>>& PropertiesContainer::GetProperties() const
	{
		return _properties;
	}
}

#endif //PROPERTIESCONTAINER_H

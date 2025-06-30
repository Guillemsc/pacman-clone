//
// Created by guillem on 6/29/25.
//

#ifndef SERIALIZEDPROPERTYCONTAINER_H
#define SERIALIZEDPROPERTYCONTAINER_H

#include <memory>
#include <vector>

#include "SerializedProperty.h"

namespace GEngine
{
	class SerializedPropertyContainer
	{
	public:
		template<class T>
		std::shared_ptr<SerializedProperty<T>> Add(const std::string& name, T value);

		const std::vector<std::shared_ptr<ISerializedProperty>>& GetProperties() const;

	private:
		std::vector<std::shared_ptr<ISerializedProperty>> _properties;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class T>
	std::shared_ptr<SerializedProperty<T>> SerializedPropertyContainer::Add(const std::string& name, T value)
	{
		std::shared_ptr<SerializedProperty<T>> property = std::make_shared<SerializedProperty<T>>(name, value);
		_properties.push_back(property);
		return property;
	}

	inline const std::vector<std::shared_ptr<ISerializedProperty>>& SerializedPropertyContainer::GetProperties() const
	{
		return _properties;
	}
}

#endif //SERIALIZEDPROPERTYCONTAINER_H

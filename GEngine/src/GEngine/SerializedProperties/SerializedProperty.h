//
// Created by guillem on 6/29/25.
//

#ifndef SERIALIZEDPROPERTY_H
#define SERIALIZEDPROPERTY_H

#include <string>

namespace GEngine
{
	class ISerializedProperty
	{
	public:
		virtual const std::string& GetName() const = 0;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class TValue>
	class SerializedProperty : public ISerializedProperty
	{
	public:
		explicit SerializedProperty(const std::string &name, TValue value);

		const std::string& GetName() const override;
		TValue GetValue() const;
		void SetValue(const TValue& value);

	private:
		std::string _name;
		TValue _value;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class TValue>
	SerializedProperty<TValue>::SerializedProperty(const std::string &name, TValue value)
	{
		_name = name;
		_value = value;
	}

	template<class TValue>
	const std::string & SerializedProperty<TValue>::GetName() const
	{
		return _name;
	}

	template<class TValue>
	TValue SerializedProperty<TValue>::GetValue() const
	{
		return _value;
	}

	template<class TValue>
	void SerializedProperty<TValue>::SetValue(const TValue &value)
	{
		_value = value;
	}
}

#endif //SERIALIZEDPROPERTY_H

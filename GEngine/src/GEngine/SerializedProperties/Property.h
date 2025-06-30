//
// Created by guillem on 6/29/25.
//

#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>

namespace GEngine
{
	class IProperty
	{
	public:
		virtual const std::string& GetName() const = 0;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class TValue>
	class Property : public IProperty
	{
	public:
		explicit Property(const std::string &name, TValue value);

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
	Property<TValue>::Property(const std::string &name, TValue value)
	{
		_name = name;
		_value = value;
	}

	template<class TValue>
	const std::string & Property<TValue>::GetName() const
	{
		return _name;
	}

	template<class TValue>
	TValue Property<TValue>::GetValue() const
	{
		return _value;
	}

	template<class TValue>
	void Property<TValue>::SetValue(const TValue &value)
	{
		_value = value;
	}
}

#endif //SERIALIZEDPROPERTY_H

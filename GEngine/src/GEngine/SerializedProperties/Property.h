//
// Created by guillem on 6/29/25.
//

#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>

#include "GEngine/Events/Event.h"

namespace GEngine
{
	class GEngineObject;

	class IProperty
	{
	public:
		virtual const std::string& GetName() const = 0;

		virtual std::weak_ptr<GEngineObject> GetObjectValue() = 0;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class TValue>
	class Property : public IProperty
	{
	public:
		explicit Property(const std::string &name, TValue value);

		const std::string& GetName() const override;

		std::weak_ptr<GEngineObject> GetObjectValue() override;

		TValue GetValue() const;
		void SetValue(const TValue& value, bool raiseChange = true);

		void RegisterOnChanged(std::function<void(const TValue&)> callback);

	private:
		std::string _name;
		TValue _value;
		Event<const TValue&> _changedEvent;
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
	std::weak_ptr<GEngineObject> Property<TValue>::GetObjectValue()
	{
		if constexpr (std::is_same_v<TValue, std::shared_ptr<GEngineObject>>)
		{
			return _value;
		}
		else if constexpr (std::is_convertible_v<TValue, std::shared_ptr<void>>)
		{
			// Try dynamic_pointer_cast if TValue is a shared_ptr to derived
			auto shared = std::dynamic_pointer_cast<GEngineObject>(_value);
			return shared;
		}
		else
		{
			return {};
		}
	}

	template<class TValue>
	TValue Property<TValue>::GetValue() const
	{
		return _value;
	}

	template<class TValue>
	void Property<TValue>::SetValue(const TValue &value, const bool raiseChange)
	{
		_value = value;

		if (raiseChange)
		{
			_changedEvent.Invoke(value);
		}
	}

	template<class TValue>
	void Property<TValue>::RegisterOnChanged(std::function<void(const TValue&)> callback)
	{
		_changedEvent.Add(callback);
	}
}

#endif //SERIALIZEDPROPERTY_H

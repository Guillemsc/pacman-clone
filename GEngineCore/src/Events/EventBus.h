//
// Created by guillem on 6/7/25.
//

#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <functional>
#include <typeindex>

#include "Extensions/UnorderedMapExtensions.h"

namespace GEngineCore
{
	template<typename EventType>
	class EventBus
	{
	public:
		using HandlerFunc = std::function<void(const EventType&)>;

	public:
		std::uint32_t Subscribe(const HandlerFunc& method);
		bool Unsubscribe(std::uint32_t handler);
		void Emit(const EventType &event) const;

	private:
		std::unordered_map<std::uint32_t, HandlerFunc> _handlersToMethods;
		std::uint32_t _nextHandlerId;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<typename EventType>
	std::uint32_t EventBus<EventType>::Subscribe(const HandlerFunc &method)
	{
		std::int32_t handlerIndex = _nextHandlerId;
		++_nextHandlerId;

		_handlersToMethods.insert(std::make_pair(handlerIndex, method));

		return handlerIndex;
	}

	template<typename EventType>
	bool EventBus<EventType>::Unsubscribe(std::uint32_t handler)
	{
		return UnorderedMapRemoveKey(_handlersToMethods, handler);
	}

	template<typename EventType>
	void EventBus<EventType>::Emit(const EventType &event) const
	{
		for (auto it = _handlersToMethods.begin(); it != _handlersToMethods.end(); ++it)
		{
			it->second(event);
		}
	}
}

#endif //EVENTBUS_H

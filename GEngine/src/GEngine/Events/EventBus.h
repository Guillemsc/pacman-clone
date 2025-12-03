//
// Created by guillem on 6/7/25.
//

#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <cstdint>
#include <functional>
#include <typeindex>

#include "Extensions/UnorderedMapExtensions.h"

namespace GEngine
{
	template<typename... Args>
	class EventBus
	{
	public:
		using HandlerFunc = std::function<void(Args...)>;

	public:
		std::uint32_t Subscribe(const HandlerFunc& method)
		{
			std::int32_t handlerIndex = _nextHandlerId;
			++_nextHandlerId;

			_handlersToMethods.insert(std::make_pair(handlerIndex, method));

			return handlerIndex;
		}

		bool Unsubscribe(std::uint32_t handler)
		{
			return UnorderedMapRemoveKey(_handlersToMethods, handler);
		}

		void Emit(const Args... args) const
		{
			for (auto it = _handlersToMethods.begin(); it != _handlersToMethods.end(); ++it)
			{
				it->second(args...);
			}
		}

		void operator()(Args... args) const
		{
			Invoke(args...);
		}

	private:
		std::unordered_map<std::uint32_t, HandlerFunc> _handlersToMethods;
		std::uint32_t _nextHandlerId = 0;
	};
}

#endif //EVENTBUS_H

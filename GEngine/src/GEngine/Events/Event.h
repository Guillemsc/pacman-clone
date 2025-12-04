//
// Created by guillem on 6/8/25.
//

#ifndef EVENT_H
#define EVENT_H
#include <functional>
#include <algorithm>

namespace GEngine
{
	template<typename... Args>
	class SubscribeEvent
	{
	public:
		virtual void Add(const std::function<void(Args...)>& handler) = 0;
	};

	template<typename... Args>
	class UnsubscribeEvent
	{
	public:
		virtual void Remove(const std::function<void(Args...)>& handler) = 0;
	};

	template<typename... Args>
	class RegisterEvent : public SubscribeEvent<Args...>, public UnsubscribeEvent<Args...>
	{

	};

	template<typename... Args>
	class Event final : public RegisterEvent<Args...>
	{
	public:
		using Handler = std::function<void(Args...)>;

		void Clear()
		{
			_handlers.clear();
		}

		void Add(const Handler& handler) override
		{
			_handlers.push_back(handler);
		}

		void Remove(const Handler& handler) override
		{
			_handlers.erase(
				std::remove_if(
					_handlers.begin(),
					_handlers.end(),
					[&](const Handler& h) { return h.target_type() == handler.target_type(); }),
				_handlers.end()
				);
		}

		void Invoke(Args... args) const
		{
			for (const auto& handler : _handlers)
			{
				handler(args...);
			}
		}

		void operator()(Args... args) const
		{
			Invoke(args...);
		}

	private:
		std::vector<Handler> _handlers;
	};
}

#endif //EVENT_H

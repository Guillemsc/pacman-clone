//
// Created by guillem on 6/8/25.
//

#ifndef EVENT_H
#define EVENT_H
#include <functional>

namespace GEngineCore
{
	template<typename... Args>
	class Event
	{
	public:
		using Handler = std::function<void(Args...)>;

		void Clear()
		{
			_handlers.clear();
		}

		void Add(const Handler& handler)
		{
			_handlers.push_back(handler);
		}

		void Remove(const Handler& handler)
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

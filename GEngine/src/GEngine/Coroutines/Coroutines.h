//
// Created by guillem on 7/27/25.
//

#ifndef COROUTINES_H
#define COROUTINES_H

#include "tokoro.h"

namespace GEngine
{
	class Coroutines
	{
	public:
		static tokoro::Scheduler& Scheduler();

		template <typename AsyncFunc, typename... Args>
		requires tokoro::internal::ReturnsAsync<AsyncFunc, Args...>
		[[nodiscard]] static tokoro::Handle<tokoro::internal::AsyncValueT<AsyncFunc, Args...>> Start(
			AsyncFunc&& func,
			Args&&... funcArgs
			)
		{
			return Scheduler().Start(std::forward<AsyncFunc>(func), std::forward<Args>(funcArgs)...);
		}
	};
}

#endif //COROUTINES_H

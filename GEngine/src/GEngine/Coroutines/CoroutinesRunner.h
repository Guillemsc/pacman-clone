//
// Created by guillem on 12/4/25.
//

#ifndef COROUTINESRUNNER_H
#define COROUTINESRUNNER_H

#include "tokoro.h"
#include "GEngine/Tickables/Tickable.h"

namespace GEngine
{
	class CoroutinesRunner
	{
		friend class CoroutinesModule;

	public:
		template <typename AsyncFunc, typename... Args> requires tokoro::internal::ReturnsAsync<AsyncFunc, Args...>
		[[nodiscard]] tokoro::Handle<tokoro::internal::AsyncValueT<AsyncFunc, Args...>> Start(
			AsyncFunc&& func,
			Args&&... funcArgs
			);

	private:
		void Tick();

	private:
		tokoro::Scheduler _scheduler;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<typename AsyncFunc, typename ... Args> requires tokoro::internal::ReturnsAsync<AsyncFunc, Args...>
	tokoro::Handle<tokoro::internal::AsyncValueT<AsyncFunc, Args...>> CoroutinesRunner::Start(
		AsyncFunc &&func,
		Args &&...funcArgs
		)
	{
		return _scheduler.Start(std::forward<AsyncFunc>(func), std::forward<Args>(funcArgs)...);
	}
}

#endif //COROUTINESRUNNER_H

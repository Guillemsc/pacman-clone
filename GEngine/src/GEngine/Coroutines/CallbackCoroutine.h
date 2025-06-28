//
// Created by guillem on 6/28/25.
//

#ifndef CALLBACKCOROUTINE_H
#define CALLBACKCOROUTINE_H

#include <functional>

#include "Coroutine.h"

namespace GEngine
{
	class CallbackCoroutine final : public Coroutine
	{
	public:
		explicit CallbackCoroutine(const std::function<void()>& callback);

		bool MoveNext() override;

	private:
		std::function<void()> _callback;
	};
}

#endif //CALLBACKCOROUTINE_H

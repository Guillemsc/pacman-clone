//
// Created by guillem on 6/28/25.
//

#include "CallbackCoroutine.h"

namespace GEngine
{
	CallbackCoroutine::CallbackCoroutine(const std::function<void()> &callback)
	{
		_callback = callback;
	}

	bool CallbackCoroutine::MoveNext()
	{
		_callback();
		return true;
	}
} // GEngineCore
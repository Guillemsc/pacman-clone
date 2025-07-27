//
// Created by guillem on 7/28/25.
//

#include "CallbackTween.h"

namespace GEngine
{
	CallbackTween::CallbackTween(const std::function<void()>& callback)
	{
		_callback = std::move(callback);
	}

	void CallbackTween::OnStart()
	{
		_callback();
		CompleteMain();
	}
}
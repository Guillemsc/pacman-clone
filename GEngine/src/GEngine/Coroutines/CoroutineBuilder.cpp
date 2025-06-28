//
// Created by guillem on 6/28/25.
//

#include "CoroutineBuilder.h"

#include "CallbackCoroutine.h"
#include "NestedCoroutine.h"

namespace GEngine
{
	CoroutineBuilder::CoroutineBuilder()
	{
		_coroutine = std::make_shared<NestedCoroutine>();
	}

	const CoroutineBuilder& CoroutineBuilder::Add(const std::shared_ptr<Coroutine> &coroutine) const
	{
		_coroutine->Add(coroutine);
		return *this;
	}

	const CoroutineBuilder & CoroutineBuilder::Add(const std::function<void()> &callback) const
	{
		_coroutine->Add(std::make_shared<CallbackCoroutine>(callback));
		return *this;
	}

	std::shared_ptr<Coroutine> CoroutineBuilder::Build() const
	{
		return _coroutine;
	}
} // GengineCore
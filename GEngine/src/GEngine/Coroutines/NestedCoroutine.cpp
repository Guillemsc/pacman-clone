//
// Created by guillem on 6/27/25.
//

#include "NestedCoroutine.h"

namespace GEngine
{
	bool NestedCoroutine::MoveNext()
	{
		while (!_coroutines.empty())
		{
			const bool canContinue = (*_coroutines.begin())->MoveNext();

			if (canContinue)
			{
				return true;
			}

			_coroutines.erase(_coroutines.begin());
		}

		return false;
	}

	void NestedCoroutine::Add(const std::shared_ptr<Coroutine> &coroutine)
	{
		if(!coroutine) return;

		_coroutines.push_back(coroutine);
	}
} // GEngineCore
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
			const bool finished = (*_coroutines.begin())->MoveNext();

			if (finished)
			{
				_coroutines.erase(_coroutines.begin());
			}
			else
			{
				return false;
			}
		}

		return true;
	}

	void NestedCoroutine::Add(const std::shared_ptr<Coroutine> &coroutine)
	{
		_coroutines.push_back(coroutine);
	}
} // GEngineCore
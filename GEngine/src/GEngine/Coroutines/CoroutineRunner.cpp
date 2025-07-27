//
// Created by guillem on 6/28/25.
//

#include "CoroutineRunner.h"

#include "Coroutine.h"
#include "CoroutineTask.h"
#include "GEngine/Extensions/VectorExtensions.h"

namespace GEngine
{
	void CoroutineRunner::Tick()
	{
		_coroutines.insert(_coroutines.end(), _newCoroutines.begin(), _newCoroutines.end());
		_newCoroutines.clear();

		for (auto it = _coroutines.begin(); it != _coroutines.end(); )
		{
			if (it->first->GetIsCancelled())
			{
				VectorExtensions::EraseOrIncrease(_coroutines, it, true);
				continue;
			}

			it->first->_isFinished = !it->second->MoveNext();

			VectorExtensions::EraseOrIncrease(_coroutines, it, it->first->_isFinished);
		}
	}

	std::weak_ptr<CoroutineTask> CoroutineRunner::Run(const std::shared_ptr<Coroutine>& coroutine)
	{
		std::shared_ptr<CoroutineTask> handler = std::make_shared<CoroutineTask>();

		handler->_isFinished = coroutine->MoveNext();

		if (!handler->_isFinished)
		{
			_newCoroutines.push_back({handler, coroutine});
		}

		return handler;
	}
} // GengineCore
//
// Created by guillem on 7/27/25.
//

#include "CoroutineSequencer.h"

#include "CoroutineRunner.h"
#include "CoroutineTask.h"
#include "GEngine/Extensions/VectorExtensions.h"

namespace GEngine
{
	CoroutineSequencer::CoroutineSequencer(const std::weak_ptr<CoroutineRunner> &runner)
	{
		_runner = runner;
	}

	void CoroutineSequencer::Run(const std::shared_ptr<Coroutine> &coroutine)
	{
		_queue.push_back(coroutine);
		Tick();
	}

	void CoroutineSequencer::Tick()
	{
		const std::shared_ptr<CoroutineTask> currentTask = _currentTask.lock();

		bool finished = true;

		if (currentTask)
		{
			finished = currentTask->GetIsFinished();
		}

		if (!finished) return;
		if (_queue.size() == 0) return;

		const std::shared_ptr<Coroutine> next = _queue.front();
		VectorExtensions::Remove(_queue, next);

		const std::shared_ptr<CoroutineRunner> runner = _runner.lock();
		if (!runner) return;

		_currentTask = runner->Run(next);
	}
}

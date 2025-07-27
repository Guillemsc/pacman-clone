//
// Created by guillem on 7/27/25.
//

#ifndef COROUTINESEQUENCER_H
#define COROUTINESEQUENCER_H

#include <memory>
#include <vector>

namespace GEngine
{
	class CoroutineRunner;
	class Coroutine;
	class CoroutineTask;

	class CoroutineSequencer
	{
	friend class CoroutinesModule;

	public:
		explicit CoroutineSequencer(const std::weak_ptr<CoroutineRunner>& runner);

		void Run(const std::shared_ptr<Coroutine>& coroutine);

	private:
		void Tick();

	private:
		std::weak_ptr<CoroutineRunner> _runner;
		std::vector<std::shared_ptr<Coroutine>> _queue;
		std::weak_ptr<CoroutineTask> _currentTask;
	};
}

#endif //COROUTINESEQUENCER_H

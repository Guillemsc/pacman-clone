//
// Created by guillem on 6/28/25.
//

#ifndef COROUTINERUNNER_H
#define COROUTINERUNNER_H

#include <memory>
#include <vector>

namespace GEngine
{
	class CoroutineTask;
	class Coroutine;

	class CoroutineRunner
	{
	public:
		void Tick();

		std::weak_ptr<CoroutineTask> Run(const std::shared_ptr<Coroutine>& coroutine);

	private:
		std::vector<std::pair<std::shared_ptr<CoroutineTask>, std::shared_ptr<Coroutine>>> _coroutines;
		std::vector<std::pair<std::shared_ptr<CoroutineTask>, std::shared_ptr<Coroutine>>> _newCoroutines;
	};
}

#endif //COROUTINERUNNER_H

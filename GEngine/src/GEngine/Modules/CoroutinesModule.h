//
// Created by guillem on 6/30/25.
//

#ifndef COROUTINESMODULE_H
#define COROUTINESMODULE_H
#include <memory>
#include <vector>

#include "tokoro.h"

namespace GEngine
{
	class CoroutineSequencer;
	class Coroutine;
	class CoroutineTask;
	class CoroutineRunner;
}

namespace GEngine
{
	class CoroutinesModule
	{
	public:
		CoroutinesModule();

		void Tick();

		std::weak_ptr<CoroutineTask> Run(const std::shared_ptr<Coroutine>& coroutine) const;

		std::weak_ptr<CoroutineSequencer> AddSequencer();
		void RemoveSequencer(const std::weak_ptr<CoroutineSequencer> &sequencerPtr);

	private:
		std::shared_ptr<CoroutineRunner> _coroutineRunner;
		std::vector<std::shared_ptr<CoroutineSequencer>> _coroutineSequencers;
	};
}

#endif //COROUTINESMODULE_H

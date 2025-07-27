//
// Created by guillem on 6/30/25.
//

#include "CoroutinesModule.h"

#include "GEngine/Coroutines/CoroutineRunner.h"
#include "GEngine/Coroutines/Coroutines.h"
#include "GEngine/Coroutines/CoroutineSequencer.h"
#include "GEngine/Extensions/VectorExtensions.h"

namespace GEngine
{
	CoroutinesModule::CoroutinesModule()
	{
		_coroutineRunner = std::make_shared<CoroutineRunner>();
	}

	void CoroutinesModule::Tick()
	{
		_coroutineRunner->Tick();

		for (int i = _coroutineSequencers.size() - 1; i >= 0; i--)
		{
			const std::shared_ptr<CoroutineSequencer> sequencer = _coroutineSequencers[i];
			sequencer->Tick();
		}

		Coroutines::Scheduler().Update();
	}

	std::weak_ptr<CoroutineTask> CoroutinesModule::Run(const std::shared_ptr<Coroutine> &coroutine) const
	{
		return _coroutineRunner->Run(coroutine);
	}

	std::weak_ptr<CoroutineSequencer> CoroutinesModule::AddSequencer()
	{
		const std::shared_ptr<CoroutineSequencer> sequencer = std::make_shared<CoroutineSequencer>(_coroutineRunner);
		_coroutineSequencers.push_back(sequencer);
		return sequencer;
	}

	void CoroutinesModule::RemoveSequencer(const std::weak_ptr<CoroutineSequencer>& sequencerPtr)
	{
		VectorExtensions::Remove(_coroutineSequencers, sequencerPtr);
	}
} // GEngine

//
// Created by guillem on 6/8/25.
//

#include "TickablesModule.h"

#include "GEngine/Extensions/VectorExtensions.h"
#include "GEngine/Tickables/Tickable.h"

namespace GEngine
{
	TickablesModule::TickablesModule()
	{

	}

	void TickablesModule::Tick() const
	{
		TickTickables();
	}

	void TickablesModule::Dispose()
	{
		_tickables.clear();
	}

	void TickablesModule::AddTickable(const std::shared_ptr<Tickable>& tickable)
	{
		_tickables.push_back(tickable);
	}

	void TickablesModule::RemoveTickable(const std::shared_ptr<Tickable> &tickable)
	{
		VectorExtensions::Remove(_tickables, tickable);
	}

	void TickablesModule::RemoveAllTickablesNow()
	{
		_tickables.clear();
	}

	void TickablesModule::TickTickables() const
	{
		for (int i = _tickables.size() - 1; i >= 0; i--)
		{
			_tickables[i]->Tick();
		}
	}
} // GEngineCore
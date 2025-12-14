//
// Created by guillem on 12/14/25.
//

#ifndef MEMORYTRACKER_H
#define MEMORYTRACKER_H

#include <atomic>
#include <cstddef>

#include "GEngine/Logging/GEngineLog.h"

namespace GEngine
{
	class MemoryTracker
	{
	public:
		static std::atomic<size_t> totalAllocated;
		static std::atomic<size_t> totalFreed;
		static bool isTracking;

		static size_t CurrentlyUsed()
		{
			return totalAllocated.load() - totalFreed.load();
		}

		static void Reset()
		{
			totalAllocated = 0;
			totalFreed = 0;
		}

		static void LogLeaks()
		{
			const size_t currentAllocated = CurrentlyUsed();

			if (currentAllocated > 0)
			{
				GENGINE_INFO("Memory leaks found: {}", currentAllocated);
			}
			else
			{
				GENGINE_INFO("No memory leaks found");
			}
		}
	};
}

#endif //MEMORYTRACKER_H

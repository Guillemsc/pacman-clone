//
// Created by guillem on 6/28/25.
//

#include "ChronoTimeSource.h"

#include <chrono>

namespace GEngine
{
	ChronoTimeSource::ChronoTimeSource()
	{
		_start = std::chrono::high_resolution_clock::now();
	}

	double ChronoTimeSource::GetTimeSeconds() const
	{
		const  std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - _start;
		return duration.count();
	}
} // GEngineCore
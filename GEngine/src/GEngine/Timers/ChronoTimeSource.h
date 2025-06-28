//
// Created by guillem on 6/28/25.
//

#ifndef CHRONOTIMESOURCE_H
#define CHRONOTIMESOURCE_H

#include <chrono>

#include "ITimeSource.h"

namespace GEngine
{
	class ChronoTimeSource : public ITimeSource
	{
	public:
		ChronoTimeSource();

		double GetTimeSeconds() const override;

	private:
		std::chrono::high_resolution_clock::time_point _start;
	};
}

#endif //CHRONOTIMESOURCE_H

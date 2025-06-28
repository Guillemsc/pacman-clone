//
// Created by guillem on 6/28/25.
//

#ifndef WAITTIMECOROUTINE_H
#define WAITTIMECOROUTINE_H

#include <memory>

#include "Coroutine.h"

namespace GEngine
{
	class ChronoTimer;

	class WaitSecondsCoroutine final : public Coroutine
	{
	public:
		explicit WaitSecondsCoroutine(double seconds);

		bool MoveNext() override;

	private:
		double _seconds = 0;
		std::unique_ptr<ChronoTimer> _timer;
	};
}

#endif //WAITTIMECOROUTINE_H

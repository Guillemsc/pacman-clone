//
// Created by guillem on 6/28/25.
//

#ifndef WAITFRAMESCOROUTINE_H
#define WAITFRAMESCOROUTINE_H

#include "Coroutine.h"

namespace GEngine
{
	class WaitFramesCoroutine final : public Coroutine
	{
	public:
		explicit WaitFramesCoroutine(int frames);

		bool MoveNext() override;

	private:
		int _framesLeft;
	};
}

#endif //WAITFRAMESCOROUTINE_H

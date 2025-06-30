//
// Created by guillem on 6/27/25.
//

#ifndef NESTEDCOROUTINE_H
#define NESTEDCOROUTINE_H

#include <memory>
#include <vector>

#include "Coroutine.h"

namespace GEngine
{
	class NestedCoroutine : public Coroutine
	{
	public:
		bool MoveNext() override;

		void Add(const std::shared_ptr<Coroutine> &coroutine);

	private:
		std::vector<std::shared_ptr<Coroutine>> _coroutines;
	};
}

#endif //NESTEDCOROUTINE_H

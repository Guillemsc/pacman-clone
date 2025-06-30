//
// Created by guillem on 6/27/25.
//

#ifndef ICOROUTINE_H
#define ICOROUTINE_H
#include <memory>

namespace GEngine
{
	class Coroutine
	{
	public:
		virtual ~Coroutine() = default;

		virtual bool MoveNext() { return false; };

		static std::shared_ptr<Coroutine> Empty();
	};
}

#endif //ICOROUTINE_H

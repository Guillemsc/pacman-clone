//
// Created by guillem on 6/27/25.
//

#ifndef ICOROUTINE_H
#define ICOROUTINE_H

namespace GEngine
{
	class Coroutine
	{
	public:
		virtual ~Coroutine() = default;

		virtual bool MoveNext() { return true; };
	};
}

#endif //ICOROUTINE_H

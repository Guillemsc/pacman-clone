//
// Created by guillem on 6/30/25.
//

#ifndef COROUTINESMODULE_H
#define COROUTINESMODULE_H
#include <memory>

namespace GEngine
{
	class Coroutine;
	class CoroutineTask;
	class CoroutineRunner;
}

namespace GEngine
{
	class CoroutinesModule
	{
	public:
		CoroutinesModule();

		void Tick() const;

		std::weak_ptr<CoroutineTask> Run(const std::shared_ptr<Coroutine>& coroutine) const;

	private:
		std::shared_ptr<CoroutineRunner> _coroutineRunner;
	};
}

#endif //COROUTINESMODULE_H

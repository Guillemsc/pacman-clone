//
// Created by guillem on 6/28/25.
//

#ifndef COROUTINEBUILDER_H
#define COROUTINEBUILDER_H

#include <functional>
#include <memory>

namespace GEngine
{
	class Coroutine;
	class NestedCoroutine;

	class CoroutineBuilder
	{
	public:
		CoroutineBuilder();

		const CoroutineBuilder& Add(const std::shared_ptr<Coroutine> &coroutine) const;
		const CoroutineBuilder& Add(const std::function<void()>& callback) const;
		std::shared_ptr<Coroutine> Build() const;

	private:
		std::shared_ptr<NestedCoroutine> _coroutine;
	};
}

#endif //COROUTINEBUILDER_H

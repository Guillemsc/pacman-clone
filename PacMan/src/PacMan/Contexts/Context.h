//
// Created by guillem on 6/30/25.
//

#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>

#include "GEngine/Coroutines/Coroutine.h"

namespace PacMan
{
	class Context
	{
	public:
		std::shared_ptr<GEngine::Coroutine> Load();
		void Start();
		void Dispose();

	protected:
		virtual std::shared_ptr<GEngine::Coroutine> OnLoad();
		virtual void OnStart();
		virtual void OnDispose();

	private:
		bool _loaded;
		bool _started;
		bool _disposed;
	};
}

#endif //CONTEXT_H

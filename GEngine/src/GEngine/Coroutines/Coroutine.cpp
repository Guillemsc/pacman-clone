//
// Created by guillem on 6/30/25.
//

#include "Coroutine.h"

namespace GEngine
{
	std::shared_ptr<Coroutine> Coroutine::Empty()
	{
		static std::shared_ptr<Coroutine> instance = std::make_shared<Coroutine>();
		return instance;
	}
}

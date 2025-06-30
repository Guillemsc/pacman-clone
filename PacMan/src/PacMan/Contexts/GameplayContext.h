//
// Created by guillem on 6/30/25.
//

#ifndef GAMEPLAYCONTEXT_H
#define GAMEPLAYCONTEXT_H

#include "Context.h"

namespace PacMan
{
	class GameplayContext : public Context
	{
		std::shared_ptr<GEngine::Coroutine> OnLoad() override;
	};
}

#endif //GAMEPLAYCONTEXT_H

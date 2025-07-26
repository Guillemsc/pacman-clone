//
// Created by guillem on 6/30/25.
//

#ifndef GAMEPLAYCONTEXT_H
#define GAMEPLAYCONTEXT_H

#include "Context.h"

namespace GEngine
{
	class Entity;
}

namespace PacMan
{
	class GameplayContext : public Context
	{
		std::shared_ptr<GEngine::Coroutine> OnLoad() override;

	private:
		std::weak_ptr<GEngine::Entity> _rootUiEntity;
		std::weak_ptr<GEngine::Entity> _rootWorldEntity;
	};
}

#endif //GAMEPLAYCONTEXT_H

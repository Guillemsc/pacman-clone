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
	class MapMovementManager;

	class GameplayContext : public Context
	{
	public:
		explicit GameplayContext(GEngine::GEngineCoreModules* modules);

		tokoro::Async<void> OnLoadAsync() override;

	private:
		std::shared_ptr<MapMovementManager> _mapMovementManager;
	};
}

#endif //GAMEPLAYCONTEXT_H

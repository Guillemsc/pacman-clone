//
// Created by guillem on 7/27/25.
//

#ifndef SHAREDCONTEXT_H
#define SHAREDCONTEXT_H

#include <iostream>

#include "Context.h"
#include "tokoro.h"

namespace PacMan
{
	// Contains initial and shared modules/logic through all the game.
	class SharedContext : public Context
	{
	public:
		explicit SharedContext(GEngine::GEngineCoreModules* modules);

		tokoro::Async<void> OnLoadAsync() override;

	private:
		tokoro::Handle<void> patrolTask;
	};
}

#endif //SHAREDCONTEXT_H

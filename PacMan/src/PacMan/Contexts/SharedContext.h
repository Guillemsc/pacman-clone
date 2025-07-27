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
	class SharedContext : public Context
	{
	public:
		SharedContext();

		tokoro::Async<void> OnLoadAsync() override;

	private:
		tokoro::Handle<void> patrolTask;
	};
}

#endif //SHAREDCONTEXT_H

//
// Created by guillem on 7/27/25.
//

#ifndef SHAREDCONTEXT_H
#define SHAREDCONTEXT_H

#include <iostream>

#include "Context.h"
#include "tokoro.h"
#include "PacMan/Shared/Camera/Data/CameraData.h"

namespace PacMan
{
	// Contains initial and shared modules/logic through all the game.
	class SharedContext : public Context
	{
	public:
		explicit SharedContext(GEngine::GEngineCoreModules* modules);

		tokoro::Async<void> OnLoadAsync() override;

	private:
		std::unique_ptr<CameraData> _cameraData;
	};
}

#endif //SHAREDCONTEXT_H

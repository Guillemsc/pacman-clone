//
// Created by guillem on 7/26/25.
//

#ifndef METACONTEXT_H
#define METACONTEXT_H

#include <memory>

#include "Context.h"
#include "GEngine/Entities/Entity.h"
#include "PacMan/Meta/MainMenu/Managers/MainMenuManager.h"
#include "PacMan/Meta/Splash/Managers/SplashManager.h"

namespace PacMan
{
	class Coroutine;

	// Contains all the Ui that's not part of the gameplay.
	class MetaContext final : public Context
	{
	public:
		explicit MetaContext(GEngine::GEngineCoreModules* modules);

		tokoro::Async<void> OnLoadAsync() override;
		void OnStart() override;
		void OnDispose() override;

	private:
		tokoro::Async<void> StartFromSplashAsync(GEngine::CancellationToken cancellationToken) const;

	private:
		std::unique_ptr<SplashManager> _splashManager;
		std::unique_ptr<MainMenuManager> _mainMenuManager;
	};
}

#endif //METACONTEXT_H

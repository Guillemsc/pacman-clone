//
// Created by guillem on 12/19/25.
//

#ifndef MAINMENUMANAGER_H
#define MAINMENUMANAGER_H
#include "tokoro.h"

namespace GEngine
{
	class CancellationToken;
	class Scene;
	class GEngineCoreModules;
}

namespace PacMan
{
	class MainMenuUiView;

	class MainMenuManager
	{
	public:
		explicit MainMenuManager(GEngine::GEngineCoreModules* modules, GEngine::Scene* scene);

		[[nodiscard]] tokoro::Async<void> ShowAsync(GEngine::CancellationToken cancellationToken);

	private:
		GEngine::GEngineCoreModules* const _modules;
		GEngine::Scene* const _scene;

		std::shared_ptr<MainMenuUiView> _mainMenuView;
	};
}

#endif //MAINMENUMANAGER_H

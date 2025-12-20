//
// Created by guillem on 12/19/25.
//

#include "MainMenuManager.h"

#include "GEngine/Coroutines/CancellationToken.h"
#include "PacMan/Meta/MainMenu/Views/MainMenuUiView.h"

namespace PacMan
{
	MainMenuManager::MainMenuManager(GEngine::GEngineCoreModules *modules, GEngine::Scene *scene)
		: _modules(modules), _scene(scene)
	{
	}

	tokoro::Async<void> MainMenuManager::ShowAsync(GEngine::CancellationToken cancellationToken)
	{
		_mainMenuView = UiView::Create<MainMenuUiView>(_modules, _scene);

		co_return;
	}
}

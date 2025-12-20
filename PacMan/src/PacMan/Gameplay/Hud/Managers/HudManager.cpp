//
// Created by guillem on 12/20/25.
//

#include "HudManager.h"

#include "PacMan/Gameplay/Hud/Views/HudUiView.h"
#include "PacMan/Shared/Views/UiView.h"

namespace PacMan
{
	HudManager::HudManager(GEngine::GEngineCoreModules *modules, GEngine::Scene *scene)
		: _modules(modules), _scene(scene)
	{
	}

	tokoro::Async<void> HudManager::ShowAsync(const GEngine::CancellationToken cancellationToken)
	{
		_hudView = UiView::Create<HudUiView>(_modules, _scene);
		co_await _hudView->ShowAsync(cancellationToken);
	}
}

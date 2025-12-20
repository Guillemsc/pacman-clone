//
// Created by guillem on 12/20/25.
//

#ifndef HUDMANAGER_H
#define HUDMANAGER_H
#include "tokoro.h"
#include "GEngine/Coroutines/CancellationToken.h"

namespace PacMan
{
	class HudUiView;
}

namespace GEngine
{
	class Scene;
	class GEngineCoreModules;
}

namespace PacMan
{
	class HudManager
	{
	public:
		explicit HudManager(GEngine::GEngineCoreModules* modules, GEngine::Scene* scene);

		[[nodiscard]] tokoro::Async<void> ShowAsync(GEngine::CancellationToken cancellationToken);

	private:
		GEngine::GEngineCoreModules* const _modules;
		GEngine::Scene* const _scene;

		std::shared_ptr<HudUiView> _hudView;
	};
}

#endif //HUDMANAGER_H

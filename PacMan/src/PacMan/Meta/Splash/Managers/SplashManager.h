//
// Created by guillem on 12/19/25.
//

#ifndef SPLASHMANAGER_H
#define SPLASHMANAGER_H

#include "tokoro.h"

namespace GEngine
{
	class GEngineCoreModules;
}

namespace GEngine
{
	class Scene;
	class CancellationToken;
}

namespace PacMan
{
	class SplashManager
	{
	public:
		SplashManager(GEngine::GEngineCoreModules* modules, GEngine::Scene* scene);

		[[nodiscard]] tokoro::Async<void> PlaySplashAsync(GEngine::CancellationToken cancellationToken) const;

	private:
		GEngine::GEngineCoreModules* const _modules;
		GEngine::Scene* const _scene;
	};
}

#endif //SPLASHMANAGER_H

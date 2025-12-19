//
// Created by guillem on 12/19/25.
//

#ifndef SPLASHMANAGER_H
#define SPLASHMANAGER_H

#include "tokoro.h"

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
		SplashManager(GEngine::Scene* scene);

		[[nodiscard]] tokoro::Async<void> PlaySplashAsync(GEngine::CancellationToken cancellationToken) const;

	private:
		GEngine::Scene* const _scene;
	};
}

#endif //SPLASHMANAGER_H

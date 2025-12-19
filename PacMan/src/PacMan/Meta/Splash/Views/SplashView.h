//
// Created by guillem on 12/19/25.
//

#ifndef SPLASHVIEW_H
#define SPLASHVIEW_H

#include <memory>

#include "tokoro.h"

namespace GEngine
{
	class GEngineCoreModules;
	class CancellationToken;
	class UiShapeRendererComponent;
	class Entity;
	class Scene;
}

namespace PacMan
{
	class SplashView
	{
	public:
		explicit SplashView(
			GEngine::GEngineCoreModules* modules,
			GEngine::Scene* scene
			);

		static std::shared_ptr<SplashView> Load(
			GEngine::GEngineCoreModules* modules,
			GEngine::Scene* scene
			);

		void Dispose() const;

		tokoro::Async<void> PlaySplashAsync(GEngine::CancellationToken cancellationToken) const;

	private:
		GEngine::GEngineCoreModules* const _modules;
		GEngine::Scene* const _scene;

		std::weak_ptr<GEngine::Entity> _rootEntity;
		std::weak_ptr<GEngine::UiShapeRendererComponent> _blackScreenImage;
	};
}

#endif //SPLASHVIEW_H

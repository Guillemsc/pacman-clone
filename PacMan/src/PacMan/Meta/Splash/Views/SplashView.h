//
// Created by guillem on 12/19/25.
//

#ifndef SPLASHVIEW_H
#define SPLASHVIEW_H

#include <memory>

namespace GEngine
{
	class Entity;
	class Scene;
}

namespace PacMan
{
	class SplashView
	{
	public:
		explicit SplashView(GEngine::Scene* scene);

		static std::shared_ptr<SplashView> Load(GEngine::Scene* scene);

		void Dispose() const;

	private:
		GEngine::Scene* const _scene;

		std::weak_ptr<GEngine::Entity> _rootEntity;
	};
}

#endif //SPLASHVIEW_H

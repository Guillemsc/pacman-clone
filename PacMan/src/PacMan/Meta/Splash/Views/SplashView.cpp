//
// Created by guillem on 12/19/25.
//

#include "SplashView.h"

#include "GEngine/Scenes/Scene.h"

namespace PacMan
{
	SplashView::SplashView(GEngine::Scene *scene)
		: _scene(scene)
	{

	}

	std::shared_ptr<SplashView> SplashView::Load(GEngine::Scene *scene)
	{
		const std::shared_ptr<SplashView> splashView = std::make_shared<SplashView>(scene);
		const std::shared_ptr<GEngine::Entity> root = scene->AddUiEntity().lock();

		splashView->_rootEntity = root;

		return splashView;
	}

	void SplashView::Dispose() const
	{
		_scene->RemoveEntity(_rootEntity);
	}
}

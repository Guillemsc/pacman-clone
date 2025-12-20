//
// Created by guillem on 12/19/25.
//

#ifndef MAINMENUVIEW_H
#define MAINMENUVIEW_H

#include "tokoro.h"
#include "GEngine/Coroutines/CancellationToken.h"
#include "PacMan/Shared/Views/UiView.h"

namespace GEngine
{
	class UiShapeRendererComponent;
}

namespace PacMan
{
	class MainMenuUiView final : public UiView
	{
	public:
		explicit MainMenuUiView(
			GEngine::GEngineCoreModules* modules,
			GEngine::Scene* scene
		);

		void BuildTree(const std::shared_ptr<GEngine::Entity> &root) override;

		tokoro::Async<void> ShowAsync(GEngine::CancellationToken cancellationToken) const;
		tokoro::Async<void> HideAsync(GEngine::CancellationToken cancellationToken) const;

	private:
		void WhenPlayButtonClicked();

	private:
		std::weak_ptr<GEngine::UiShapeRendererComponent> _blackScreenImage;
	};
}

#endif //MAINMENUVIEW_H

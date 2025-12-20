//
// Created by guillem on 12/20/25.
//

#ifndef HUDVIEW_H
#define HUDVIEW_H

#include "tokoro.h"
#include "GEngine/Coroutines/CancellationToken.h"
#include "PacMan/Shared/Views/UiView.h"

namespace GEngine
{
	class UiRenderersAlphaGroupComponent;
}

namespace PacMan
{
	class HudUiView final : public UiView
	{
	public:
		explicit HudUiView(GEngine::GEngineCoreModules* modules,GEngine::Scene* scene);

		void BuildTree(const std::shared_ptr<GEngine::Entity> &root) override;

		[[nodiscard]] tokoro::Async<void> ShowAsync(GEngine::CancellationToken cancellationToken);

	private:
		void WhenExitButtonClicked();

	private:
		std::weak_ptr<GEngine::UiRenderersAlphaGroupComponent> _alphaGroupComponent;
	};
}

#endif //HUDVIEW_H

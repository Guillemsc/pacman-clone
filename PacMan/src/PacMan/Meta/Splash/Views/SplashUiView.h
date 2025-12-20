//
// Created by guillem on 12/19/25.
//

#ifndef SPLASHVIEW_H
#define SPLASHVIEW_H

#include <memory>

#include "tokoro.h"
#include "PacMan/Shared/Views/UiView.h"

namespace GEngine
{
	class GEngineCoreModules;
	class CancellationToken;
	class UiShapeRendererComponent;
}

namespace PacMan
{
	class SplashUiView final : public UiView
	{
	public:
		explicit SplashUiView(
			GEngine::GEngineCoreModules* modules,
			GEngine::Scene* scene
			);

		void BuildTree(const std::shared_ptr<GEngine::Entity>& root) override;

		tokoro::Async<void> PlaySplashAsync(GEngine::CancellationToken cancellationToken) const;

	private:
		std::weak_ptr<GEngine::UiShapeRendererComponent> _blackScreenImage;
	};
}

#endif //SPLASHVIEW_H

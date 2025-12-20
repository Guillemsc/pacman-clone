//
// Created by guillem on 12/19/25.
//

#ifndef MAINMENUVIEW_H
#define MAINMENUVIEW_H

#include "PacMan/Shared/Views/UiView.h"

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

	private:
		void WhenPlayButtonClicked();
	};
}

#endif //MAINMENUVIEW_H

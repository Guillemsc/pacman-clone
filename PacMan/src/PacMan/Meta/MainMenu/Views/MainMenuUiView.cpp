//
// Created by guillem on 12/19/25.
//

#include "MainMenuUiView.h"

#include "GEngine/Components/UiShapeButtonComponent.h"
#include "GEngine/Components/UiShapeRendererComponent.h"
#include "GEngine/Components/UiTextRendererComponent.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Coroutines/CoroutinesRunner.h"
#include "GEngine/Modules/CoroutinesModule.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "PacMan/Contexts/ContextsStack.h"
#include "PacMan/Contexts/GameplayContext.h"

namespace PacMan
{
	MainMenuUiView::MainMenuUiView(GEngine::GEngineCoreModules *modules, GEngine::Scene *scene)
		: UiView(modules, scene, "MainMenu")
	{
	}

	void MainMenuUiView::BuildTree(const std::shared_ptr<GEngine::Entity> &root)
	{
		const std::shared_ptr<GEngine::Entity> uiEntity2 = _scene->AddUiEntity(root).lock();
		uiEntity2->AddComponent<GEngine::UiShapeRendererComponent>();
		const std::shared_ptr<GEngine::UiShapeButtonComponent> button = uiEntity2->AddComponent<GEngine::UiShapeButtonComponent>().lock();

		button->OnClick().Add([this] { WhenPlayButtonClicked(); });

		const std::shared_ptr<GEngine::Entity> uiEntity3 = _scene->AddUiEntity(root).lock();
		uiEntity3->AddComponent<GEngine::UiTextRendererComponent>();
		uiEntity3->GetUiTransform().lock()->SetAnchoredPosition({0, -100});
		uiEntity3->GetUiTransform().lock()->SetSizeDelta({200, 100});
	}

	void MainMenuUiView::WhenPlayButtonClicked()
	{
		ContextsStack* contextsStack = GEngine::ServiceLocator::Get<ContextsStack>();

		contextsStack->Pop();
		_modules->coroutines->GetMainRunner()->Start(
			&ContextsStack::PushAsync,
			contextsStack,
			std::make_shared<GameplayContext>(_modules)
			).Forget();
	}
}

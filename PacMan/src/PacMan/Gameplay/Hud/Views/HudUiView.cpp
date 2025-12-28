//
// Created by guillem on 12/20/25.
//

#include "HudUiView.h"

#include "GEngine/Components/UiRenderersAlphaGroupComponent.h"
#include "GEngine/Components/UiShapeButtonComponent.h"
#include "GEngine/Components/UiShapeRendererComponent.h"
#include "GEngine/Components/UiTextRendererComponent.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Coroutines/CoroutinesRunner.h"
#include "GEngine/Modules/CoroutinesModule.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "PacMan/Contexts/ContextsStack.h"
#include "PacMan/Contexts/GameplayContext.h"
#include "PacMan/Contexts/MetaContext.h"

namespace PacMan
{
	HudUiView::HudUiView(GEngine::GEngineCoreModules *modules, GEngine::Scene *scene)
		: UiView(modules, scene, "Hud")
	{
	}

	void HudUiView::BuildTree(const std::shared_ptr<GEngine::Entity> &root)
	{
		const std::shared_ptr<GEngine::UiRenderersAlphaGroupComponent> alphaGroupComponent
			= root->AddComponent<GEngine::UiRenderersAlphaGroupComponent>().lock();

		const std::shared_ptr<GEngine::Entity> uiEntity2 = _scene->AddUiEntity(root).lock();
		const std::shared_ptr<GEngine::UiTransformComponent> transform = uiEntity2->GetUiTransform().lock();
		transform->SetAnchorsTopLeft();
		transform->SetAnchoredPosition({ -52, -30 });
		transform->SetSizeDelta({88, 42});
		uiEntity2->AddComponent<GEngine::UiShapeRendererComponent>();
		const std::shared_ptr<GEngine::UiShapeButtonComponent> button = uiEntity2->AddComponent<GEngine::UiShapeButtonComponent>().lock();
		button->OnClick().Add([this] { WhenExitButtonClicked(); });

		const std::shared_ptr<GEngine::Entity> uiEntity3 = _scene->AddUiEntity(root).lock();
		const std::shared_ptr<GEngine::UiTransformComponent> textTransform = uiEntity3->GetUiTransform().lock();
		textTransform->SetAnchorsTopLeft();
		textTransform->SetSizeDelta({200, 100});
		textTransform->SetAnchoredPosition({ -50, -69 });
		const std::shared_ptr<GEngine::UiTextRendererComponent> textRenderer = uiEntity3->AddComponent<GEngine::UiTextRendererComponent>().lock();
		textRenderer->SetText("Exit");
		textRenderer->SetSize(2);
		textRenderer->SetHorizontalAlign(GEngine::HorizontalTextAlign::CENTER);

		_alphaGroupComponent = alphaGroupComponent;
	}

	tokoro::Async<void> HudUiView::ShowAsync(GEngine::CancellationToken cancellationToken)
	{
		co_return;
	}

	void HudUiView::WhenExitButtonClicked()
	{
		ContextsStack* contextsStack = GEngine::ServiceLocator::Get<ContextsStack>();

		contextsStack->Pop();
		_modules->coroutines->GetMainRunner()->Start(
			&ContextsStack::PushAsync,
			contextsStack,
			std::make_shared<MetaContext>(_modules, true)
			).Forget();
	}
}

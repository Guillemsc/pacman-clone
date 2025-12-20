//
// Created by guillem on 12/20/25.
//

#include "HudUiView.h"

#include "GEngine/Components/UiRenderersAlphaGroupComponent.h"
#include "GEngine/Components/UiShapeButtonComponent.h"
#include "GEngine/Components/UiShapeRendererComponent.h"
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
		transform->SetAnchoredPosition({ -30, -30 });
		uiEntity2->AddComponent<GEngine::UiShapeRendererComponent>();
		const std::shared_ptr<GEngine::UiShapeButtonComponent> button = uiEntity2->AddComponent<GEngine::UiShapeButtonComponent>().lock();
		button->OnClick().Add([this] { WhenExitButtonClicked(); });

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

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
#include "GEngine/Modules/TweensModule.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "GEngine/Tweens/InterpolationTween.h"
#include "GEngine/Tweens/Tween.h"
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
		uiEntity2->GetUiTransform().lock()->SetSizeDelta({150, 70});

		const std::shared_ptr<GEngine::Entity> uiEntity3 = _scene->AddUiEntity(root).lock();
	 	const std::shared_ptr<GEngine::UiTextRendererComponent> textRenderer = uiEntity3->AddComponent<GEngine::UiTextRendererComponent>().lock();
		textRenderer->SetText("Play");
		textRenderer->SetSize(3);
		textRenderer->SetHorizontalAlign(GEngine::HorizontalTextAlign::CENTER);
		uiEntity3->GetUiTransform().lock()->SetSizeDelta({200, 100});
		uiEntity3->GetUiTransform().lock()->SetAnchoredPosition({0, -35});

		const std::shared_ptr<GEngine::Entity> blackScreen = _scene->AddUiEntity(root).lock();
		const std::shared_ptr<GEngine::UiTransformComponent> blackScreenTransform = blackScreen->GetUiTransform().lock();
		blackScreenTransform->ExpandOnParent();
		const std::shared_ptr<GEngine::UiShapeRendererComponent> blackScreenImage = blackScreen->AddComponent<GEngine::UiShapeRendererComponent>().lock();
		blackScreenImage->SetColor(GEngine::Color01::Black.WithAlpha(1));
		_blackScreenImage = blackScreenImage;
	}

	tokoro::Async<void> MainMenuUiView::ShowAsync(const GEngine::CancellationToken cancellationToken) const
	{
		const std::shared_ptr<GEngine::UiShapeRendererComponent> blackScreenImage = _blackScreenImage.lock();
		if (!blackScreenImage) co_return;

		const std::shared_ptr<GEngine::Tween> tween = std::make_shared<GEngine::Tween>();

		tween->AddChildren(std::make_shared<GEngine::InterpolationTween<float>>(
			[blackScreenImage] { return blackScreenImage->GetColor().a; },
			[blackScreenImage](const float value) { blackScreenImage->SetColor(blackScreenImage->GetColor().WithAlpha(value)); },
			0,
			1
			));

		co_await _modules->tweens->PlayAsync(tween, cancellationToken);
	}

	tokoro::Async<void> MainMenuUiView::HideAsync(const GEngine::CancellationToken cancellationToken) const
	{
		const std::shared_ptr<GEngine::UiShapeRendererComponent> blackScreenImage = _blackScreenImage.lock();
		if (!blackScreenImage) co_return;

		const std::shared_ptr<GEngine::Tween> tween = std::make_shared<GEngine::Tween>();

		tween->AddChildren(std::make_shared<GEngine::InterpolationTween<float>>(
			[blackScreenImage] { return blackScreenImage->GetColor().a; },
			[blackScreenImage](const float value) { blackScreenImage->SetColor(blackScreenImage->GetColor().WithAlpha(value)); },
			1,
			1
			));

		co_await _modules->tweens->PlayAsync(tween, cancellationToken);
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

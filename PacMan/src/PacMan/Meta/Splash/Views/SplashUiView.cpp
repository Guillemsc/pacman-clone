//
// Created by guillem on 12/19/25.
//

#include "SplashUiView.h"

#include "GEngine/Components/UiShapeRendererComponent.h"
#include "GEngine/Components/UiTextureRendererComponent.h"
#include "GEngine/Components/UiTransformComponent.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Coroutines/CancellationToken.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Modules/TweensModule.h"
#include "GEngine/Resources/TextureResource.h"
#include "GEngine/Scenes/Scene.h"
#include "GEngine/Tweens/InterpolationTween.h"
#include "GEngine/Tweens/Tween.h"
#include "GEngine/Tweens/WaitTween.h"

namespace PacMan
{
	SplashUiView::SplashUiView(GEngine::GEngineCoreModules* modules, GEngine::Scene *scene)
		: UiView(modules, scene, "Splash")
	{

	}

	tokoro::Async<void> SplashUiView::PlaySplashAsync(const GEngine::CancellationToken cancellationToken) const
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

		tween->AddChildren(std::make_shared<GEngine::WaitTween>(2));

		tween->AddChildren(std::make_shared<GEngine::InterpolationTween<float>>(
			[blackScreenImage] { return blackScreenImage->GetColor().a; },
			[blackScreenImage](const float value) { blackScreenImage->SetColor(blackScreenImage->GetColor().WithAlpha(value)); },
			1,
			1
			));

		co_await _modules->tweens->PlayAsync(tween, cancellationToken);
	}

	void SplashUiView::BuildTree(const std::shared_ptr<GEngine::Entity>& root)
	{
		const std::weak_ptr<GEngine::TextureResource> poweredByTexture = _modules->resources->GetResource<GEngine::TextureResource>("meta/PoweredBy.png");
		const std::shared_ptr<GEngine::Entity> poweredBy = _scene->AddUiEntity(root).lock();
		const std::shared_ptr<GEngine::UiTransformComponent> poweredByTransform = poweredBy->GetUiTransform().lock();
		poweredByTransform->SetSizeDelta({ 450, 100 });
		const std::shared_ptr<GEngine::UiTextureRendererComponent> poweredByRenderer = poweredBy->AddComponent<GEngine::UiTextureRendererComponent>().lock();
		poweredByRenderer->SetTexture(poweredByTexture);
		poweredByRenderer->SetPreserveAspectRatio(true);

		const std::shared_ptr<GEngine::Entity> blackScreen = _scene->AddUiEntity(root).lock();
		const std::shared_ptr<GEngine::UiTransformComponent> blackScreenTransform = blackScreen->GetUiTransform().lock();
		blackScreenTransform->ExpandOnParent();
		const std::shared_ptr<GEngine::UiShapeRendererComponent> blackScreenImage = blackScreen->AddComponent<GEngine::UiShapeRendererComponent>().lock();
		blackScreenImage->SetColor(GEngine::Color01::Black.WithAlpha(1));
		_blackScreenImage = blackScreenImage;
	}
}

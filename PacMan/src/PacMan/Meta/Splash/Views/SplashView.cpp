//
// Created by guillem on 12/19/25.
//

#include "SplashView.h"

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

namespace PacMan
{
	SplashView::SplashView(GEngine::GEngineCoreModules* modules, GEngine::Scene *scene)
		: _modules(modules), _scene(scene)
	{

	}

	std::shared_ptr<SplashView> SplashView::Load(
		GEngine::GEngineCoreModules* modules,
		GEngine::Scene *scene
		)
	{
		const std::shared_ptr<SplashView> splashView = std::make_shared<SplashView>(modules, scene);

		const std::shared_ptr<GEngine::Entity> root = scene->AddUiEntity().lock();
		root->GetUiTransform().lock()->ExpandOnParent();

		const std::weak_ptr<GEngine::TextureResource> poweredByTexture = modules->resources->GetResource<GEngine::TextureResource>("meta/PoweredBy.png");
		const std::shared_ptr<GEngine::Entity> poweredBy = scene->AddUiEntity(root).lock();
		const std::shared_ptr<GEngine::UiTransformComponent> poweredByTransform = poweredBy->GetUiTransform().lock();
		poweredByTransform->SetSizeDelta({ 450, 100 });
		const std::shared_ptr<GEngine::UiTextureRendererComponent> poweredByRenderer = poweredBy->AddComponent<GEngine::UiTextureRendererComponent>().lock();
		poweredByRenderer->SetTexture(poweredByTexture);
		poweredByRenderer->SetPreserveAspectRatio(true);

		const std::shared_ptr<GEngine::Entity> blackScreen = scene->AddUiEntity(root).lock();
		const std::shared_ptr<GEngine::UiTransformComponent> blackScreenTransform = blackScreen->GetUiTransform().lock();
		blackScreenTransform->ExpandOnParent();
		const std::shared_ptr<GEngine::UiShapeRendererComponent> blackScreenImage = blackScreen->AddComponent<GEngine::UiShapeRendererComponent>().lock();
		blackScreenImage->SetColor(GEngine::Color01::Black.WithAlpha(1));
		splashView->_blackScreenImage = blackScreenImage;

		splashView->_rootEntity = root;

		return splashView;
	}

	void SplashView::Dispose() const
	{
		_scene->RemoveEntity(_rootEntity);
	}

	tokoro::Async<void> SplashView::PlaySplashAsync(const GEngine::CancellationToken cancellationToken) const
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
}

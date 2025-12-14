//
// Created by guillem on 7/27/25.
//

#include "DevelopmentTweensExample.h"

#include "GEngine/Components/Camera2dComponent.h"
#include "GEngine/Components/CameraComponent.h"
#include "GEngine/Components/Shape2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Modules/EntitiesModule.h"
#include "GEngine/Modules/TweensModule.h"
#include "GEngine/Tweens/CallbackTween.h"
#include "GEngine/Tweens/Easing.h"
#include "GEngine/Tweens/InterpolationTween.h"
#include "spdlog/spdlog.h"

namespace GEngine
{
	class EntitiesModule;

	DevelopmentTweensExample::DevelopmentTweensExample() : Game("DevelopmentTweensExample")
	{
	}

	void DevelopmentTweensExample::Init()
	{
		const std::shared_ptr<Entity> cameraEntity = _modules->entities->AddWorldEntity().lock();
		cameraEntity->SetName("Camera");
		cameraEntity->AddComponent<Camera2dComponent>();

		const std::shared_ptr<Entity> entity = _modules->entities->AddWorldEntity().lock();
		entity->AddComponent<Shape2dRendererComponent>();
		std::shared_ptr<TransformComponent> transform = entity->GetTransform().lock();

		_tween = std::make_shared<Tween>();

		_tween->AddChildren(std::make_shared<InterpolationTween<float>>(
			[transform] { return transform->GetLocalPosition().x; },
			[transform](const float value) { transform->SetLocalPositionX(value); },
			50,
			1
		));

		_tween->AddChildren(std::make_shared<CallbackTween>(
			[]{ spdlog::info("Hi"); }
		));

		_tween->AddChildren(std::make_shared<InterpolationTween<float>>(
			[transform] { return transform->GetLocalPosition().y; },
			[transform](const float value) { transform->SetLocalPositionY(value); },
			50,
			1
		));

		_tween->AddChildren(std::make_shared<InterpolationTween<glm::vec2>>(
			[transform] { return transform->GetLocalPositionXY(); },
			[transform](const glm::vec2 value) { transform->SetLocalPositionXY(value); },
			glm::vec2(0, 0),
			1
		));

		_tween->AddChildren(std::make_shared<InterpolationTween<glm::vec2>>(
			[transform] { return transform->GetLocalScale(); },
			[transform](const glm::vec2 value) { transform->SetLocalScaleXY(value); },
			glm::vec2(2, 2),
			1
			),
			ChildrenTweenSequenceMode::JOIN
		);

		_tween->SetEasing(EasingType::OUT_QUAD);

		_modules->tweens->Play(_tween);
	}

	void DevelopmentTweensExample::Tick(const float deltaTime)
	{

	}

	void DevelopmentTweensExample::Dispose()
	{
	}
}

//
// Created by guillem on 12/3/25.
//

#include "PlayerAnimationComponent.h"

#include "GEngine/Components/Sprite2dAnimatorComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "glm/vec2.hpp"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"

namespace PacMan
{
	PlayerAnimationComponent::PlayerAnimationComponent(
		GEngine::GEngineCoreModules *modules,
		const std::weak_ptr<GEngine::Entity> &entity,
		const std::weak_ptr<MapMovementComponent> &mapMovementComponent,
		const std::weak_ptr<GEngine::Sprite2dRendererComponent> &spriteRendererComponent,
		const std::weak_ptr<GEngine::Sprite2dAnimatorComponent> &spriteAnimatorComponent
		)
		: Component(modules, entity),
		_mapMovementComponent(mapMovementComponent),
		_spriteRendererComponent(spriteRendererComponent),
		_spriteAnimatorComponent(spriteAnimatorComponent)
	{
	}

	void PlayerAnimationComponent::OnTick()
	{
		const std::shared_ptr<GEngine::TransformComponent> transform = GetEntity().lock()->GetTransform().lock();

		const std::shared_ptr<MapMovementComponent> mapMovement = _mapMovementComponent.lock();
		if (!mapMovement) return;

		const std::shared_ptr<GEngine::Sprite2dRendererComponent> spriteRenderer = _spriteRendererComponent.lock();
		if (!spriteRenderer) return;

		const std::shared_ptr<GEngine::Sprite2dAnimatorComponent> spriteAnimator = _spriteAnimatorComponent.lock();
		if (!spriteAnimator) return;

		const glm::vec2 directionVector = mapMovement->GetGridDirectionVector();

		const bool flipX = directionVector.x < 0;

		spriteRenderer->SetFlippedX(flipX);

		if (directionVector.x < 0)
		{
			transform->SetLocalRotationEulerDegreesZ(0);
		}
		else if (directionVector.x > 0)
		{
			transform->SetLocalRotationEulerDegreesZ(0);
		}
		else if (directionVector.y > 0)
		{
			transform->SetLocalRotationEulerDegreesZ(90);
		}
		else if (directionVector.y < 0)
		{
			transform->SetLocalRotationEulerDegreesZ(-90);
		}

		const float distanceMoved = mapMovement->GetDistanceMovedThisFrame();
		spriteAnimator->SetAnimationSpeed(distanceMoved * 0.06f);
	}
}

//
// Created by guillem on 12/13/25.
//

#include "GhostAnimationComponent.h"

#include "GhostStateComponent.h"
#include "GEngine/Components/Sprite2dAnimatorComponent.h"
#include "GEngine/Components/Sprite2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "PacMan/Gameplay/Ghosts/Data/GhostsStateData.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"

namespace PacMan
{
	GhostAnimationComponent::GhostAnimationComponent(
		GEngine::GEngineCoreModules *modules,
		const std::weak_ptr<GEngine::Entity> &entity,
		GhostsStateData *ghostsStateData,
		const std::weak_ptr<GhostStateComponent>& ghostStateComponent,
		const std::weak_ptr<MapMovementComponent>& mapMovementComponent,
		const std::weak_ptr<GEngine::Sprite2dRendererComponent> &spriteRendererComponent,
		const std::weak_ptr<GEngine::Sprite2dAnimatorComponent> &spriteAnimatorComponent
		) : Component(modules, entity),
		_ghostsStateData(ghostsStateData),
		_ghostStateComponent(ghostStateComponent),
		_mapMovementComponent(mapMovementComponent),
		_spriteRendererComponent(spriteRendererComponent),
		_spriteAnimatorComponent(spriteAnimatorComponent)
	{
	}

	void GhostAnimationComponent::OnTick()
	{
		const std::shared_ptr<GEngine::TransformComponent> transform = GetEntity().lock()->GetTransform().lock();

		const std::shared_ptr<MapMovementComponent> mapMovement = _mapMovementComponent.lock();
		if (!mapMovement) return;

		const std::shared_ptr<GEngine::Sprite2dRendererComponent> spriteRenderer = _spriteRendererComponent.lock();
		if (!spriteRenderer) return;

		const std::shared_ptr<GEngine::Sprite2dAnimatorComponent> spriteAnimator = _spriteAnimatorComponent.lock();
		if (!spriteAnimator) return;

		const glm::vec2 directionVector = mapMovement->GetGridDirectionVector();

		if (directionVector.x < 0)
		{
			const std::string leftAnimation = GetLeftAnimation();
			spriteAnimator->PlayAnimation(leftAnimation);
		}
		else if (directionVector.x > 0)
		{
			const std::string rightAnimation = GetRightAnimation();
			spriteAnimator->PlayAnimation(rightAnimation);
		}
		else if (directionVector.y > 0)
		{
			const std::string upAnimation = GetUpAnimation();
			spriteAnimator->PlayAnimation(upAnimation);
		}
		else if (directionVector.y < 0)
		{
			const std::string downAnimation = GetDownAnimation();
			spriteAnimator->PlayAnimation(downAnimation);
		}

		const float distanceMoved = mapMovement->GetDistanceMovedThisFrame();
		spriteAnimator->SetAnimationSpeed(distanceMoved * 0.06f);
	}

	std::string GhostAnimationComponent::GetLeftAnimation() const
	{
		const std::shared_ptr<GhostStateComponent> state = _ghostStateComponent.lock();
		if (!state) return "";

		if (state->isReturningToPrision)
		{
			return "dead_left";
		}

		if (_ghostsStateData->ghostsMode == GhostMode::FRIGHTENED)
		{
			if (_ghostsStateData->ghostsFrightenedAlmostFinished)
			{
				return "scared_almost_finished";
			}

			return "scared";
		}

		return "move_left";
	}

	std::string GhostAnimationComponent::GetRightAnimation() const
	{
		const std::shared_ptr<GhostStateComponent> state = _ghostStateComponent.lock();
		if (!state) return "";

		if (state->isReturningToPrision)
		{
			return "dead_right";
		}

		if (_ghostsStateData->ghostsMode == GhostMode::FRIGHTENED)
		{
			if (_ghostsStateData->ghostsFrightenedAlmostFinished)
			{
				return "scared_almost_finished";
			}

			return "scared";
		}

		return "move_right";
	}

	std::string GhostAnimationComponent::GetUpAnimation() const
	{
		const std::shared_ptr<GhostStateComponent> state = _ghostStateComponent.lock();
		if (!state) return "";

		if (state->isReturningToPrision)
		{
			return "dead_up";
		}

		if (_ghostsStateData->ghostsMode == GhostMode::FRIGHTENED)
		{
			if (_ghostsStateData->ghostsFrightenedAlmostFinished)
			{
				return "scared_almost_finished";
			}

			return "scared";
		}

		return "move_up";
	}

	std::string GhostAnimationComponent::GetDownAnimation() const
	{
		const std::shared_ptr<GhostStateComponent> state = _ghostStateComponent.lock();
		if (!state) return "";

		if (state->isReturningToPrision)
		{
			return "dead_down";
		}

		if (_ghostsStateData->ghostsMode == GhostMode::FRIGHTENED)
		{
			if (_ghostsStateData->ghostsFrightenedAlmostFinished)
			{
				return "scared_almost_finished";
			}

			return "scared";
		}

		return "move_down";
	}
}

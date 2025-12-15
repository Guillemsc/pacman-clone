//
// Created by guillem on 12/1/25.
//

#include "Sprite2dAnimatorComponent.h"

#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Extensions/MapExtensions.h"
#include "GEngine/Extensions/VectorExtensions.h"
#include "GEngine/Modules/TimeModule.h"

namespace GEngine
{
	Sprite2dAnimatorComponent::Sprite2dAnimatorComponent(
		GEngineCoreModules *modules,
		const std::weak_ptr<Entity> &entity
		) : Component(modules, entity)
	{
	}

	void Sprite2dAnimatorComponent::OnTick()
	{
		if (_animations.empty()) return;

		const std::shared_ptr<Sprite2dRendererComponent> spriteRenderer = _sprite2dRenderer.lock();
		if (!spriteRenderer) return;

		const float deltaTime = modules->time->GetDeltaTime();
		_currentAnimationTime += deltaTime;

		const Sprite2dAnimation& animation = _animations[_currentAnimationIndex];

		if (animation.animationFrames.size() == 0) return;

		if (_currentAnimationTime > animation.duration)
		{
			_currentAnimationTime = 0;
			++_currentAnimationFrameIndex;

			if (_currentAnimationFrameIndex >= animation.animationFrames.size())
			{
				_currentAnimationFrameIndex = 0;
			}
		}

		const std::int32_t currentAnimationSpriteIndex = animation.animationFrames[_currentAnimationFrameIndex];

		spriteRenderer->SetSprite(animation.spriteResource);
		spriteRenderer->SetSpriteIndex(currentAnimationSpriteIndex);
	}

	void Sprite2dAnimatorComponent::SetSprite2dRenderer(
		const std::weak_ptr<Sprite2dRendererComponent> &sprite2dRenderer)
	{
		_sprite2dRenderer = sprite2dRenderer;
	}

	void Sprite2dAnimatorComponent::AddAnimation(const Sprite2dAnimation &animation)
	{
		_animations.push_back(animation);
		_animationNamesByAnimationIndex[animation.name] = _animations.size() - 1;
	}

	void Sprite2dAnimatorComponent::PlayAnimation(const std::string &animationName)
	{
		const std::optional<int> optionalIndex = MapExtensions::GetValue(_animationNamesByAnimationIndex, animationName);
		if (!optionalIndex.has_value()) return;

		_currentAnimationIndex = optionalIndex.value();
	}
}

//
// Created by guillem on 12/1/25.
//

#ifndef SPRITE2DANIMATORCOMPONENT_H
#define SPRITE2DANIMATORCOMPONENT_H

#include <memory>

#include "Component.h"
#include "Sprite2dRendererComponent.h"
#include "GEngine/Sprite2dAnimator/Sprite2dAnimation.h"

namespace GEngine
{
	class Entity;
	class GEngineCoreModules;

	class Sprite2dAnimatorComponent final : public Component
	{
	public:
		explicit Sprite2dAnimatorComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		constexpr const char* GetTypeName() override { return "Sprite2dAnimator"; }

		void OnTick() override;

		void SetSprite2dRenderer(const std::weak_ptr<Sprite2dRendererComponent>& sprite2dRenderer);
		void AddAnimation(const Sprite2dAnimation& animation);

	private:
		std::weak_ptr<Sprite2dRendererComponent> _sprite2dRenderer;

		std::vector<Sprite2dAnimation> _animations;
		std::int32_t _currentAnimationIndex = 0;
		std::int32_t _currentAnimationFrameIndex = 0;
		float _currentAnimationTime = 0;
	};
}

#endif //SPRITE2DANIMATORCOMPONENT_H

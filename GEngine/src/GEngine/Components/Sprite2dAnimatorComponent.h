//
// Created by guillem on 12/1/25.
//

#ifndef SPRITE2DANIMATORCOMPONENT_H
#define SPRITE2DANIMATORCOMPONENT_H

#include <map>
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
		REGISTER_COMPONENT(Sprite2dAnimatorComponent)

	public:
		explicit Sprite2dAnimatorComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		void OnTick() override;

		void SetSprite2dRenderer(const std::weak_ptr<Sprite2dRendererComponent>& sprite2dRenderer);
		void AddAnimation(const Sprite2dAnimation& animation);

		void PlayAnimation(const std::string& animationName);

	private:
		std::weak_ptr<Sprite2dRendererComponent> _sprite2dRenderer;

		std::vector<Sprite2dAnimation> _animations;
		std::map<std::string, int> _animationNamesByAnimationIndex;
		std::int32_t _currentAnimationIndex = 0;
		std::int32_t _currentAnimationFrameIndex = 0;
		float _currentAnimationTime = 0;
	};
}

#endif //SPRITE2DANIMATORCOMPONENT_H

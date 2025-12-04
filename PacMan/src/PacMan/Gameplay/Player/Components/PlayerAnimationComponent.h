//
// Created by guillem on 12/3/25.
//

#ifndef PLAYERANIMATIONCOMPONENT_H
#define PLAYERANIMATIONCOMPONENT_H

#include "GEngine/Components/Component.h"

namespace GEngine
{
	class Sprite2dRendererComponent;
	class Sprite2dAnimatorComponent;
}

namespace PacMan
{
	class MapMovementComponent;

	class PlayerAnimationComponent final : public GEngine::Component
	{
		REGISTER_COMPONENT(PlayerAnimationComponent)

	public:
		explicit PlayerAnimationComponent(GEngine::GEngineCoreModules* modules, const std::weak_ptr<GEngine::Entity> &entity);

		void OnTick() override;

		void Init(
			const std::weak_ptr<MapMovementComponent>& mapMovementComponent,
			const std::weak_ptr<GEngine::Sprite2dRendererComponent>& spriteRendererComponent,
			const std::weak_ptr<GEngine::Sprite2dAnimatorComponent>& spriteAnimatorComponent
			);

	private:
		std::weak_ptr<MapMovementComponent> _mapMovementComponent;
		std::weak_ptr<GEngine::Sprite2dRendererComponent> _spriteRendererComponent;
		std::weak_ptr<GEngine::Sprite2dAnimatorComponent> _spriteAnimatorComponent;
	};
}

#endif //PLAYERANIMATIONCOMPONENT_H

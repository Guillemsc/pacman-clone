//
// Created by guillem on 12/13/25.
//

#ifndef GHOSTANIMATIONCOMPONENT_H
#define GHOSTANIMATIONCOMPONENT_H

#include <string>

#include "GEngine/Components/Component.h"

namespace GEngine
{
	class Sprite2dAnimatorComponent;
	class Sprite2dRendererComponent;
}

namespace PacMan
{
	class GhostStateComponent;
	class MapMovementComponent;
	struct GhostsStateData;

	class GhostAnimationComponent final : public GEngine::Component
	{
		REGISTER_COMPONENT(GhostAnimationComponent)

	public:
		explicit GhostAnimationComponent(
			GEngine::GEngineCoreModules* modules,
			const std::weak_ptr<GEngine::Entity> &entity,
			GhostsStateData* ghostsStateData,
			const std::weak_ptr<GhostStateComponent>& ghostStateComponent,
			const std::weak_ptr<MapMovementComponent>& mapMovementComponent,
			const std::weak_ptr<GEngine::Sprite2dRendererComponent> &spriteRendererComponent,
			const std::weak_ptr<GEngine::Sprite2dAnimatorComponent> &spriteAnimatorComponent
			);

		void OnTick() override;

	private:
		std::string GetLeftAnimation() const;
		std::string GetRightAnimation() const;
		std::string GetUpAnimation() const;
		std::string GetDownAnimation() const;

	private:
		GhostsStateData* const _ghostsStateData;
		std::weak_ptr<GhostStateComponent> _ghostStateComponent;
		std::weak_ptr<MapMovementComponent> _mapMovementComponent;
		std::weak_ptr<GEngine::Sprite2dRendererComponent> _spriteRendererComponent;
		std::weak_ptr<GEngine::Sprite2dAnimatorComponent> _spriteAnimatorComponent;
	};
}

#endif //GHOSTANIMATIONCOMPONENT_H

//
// Created by guillem on 12/13/25.
//

#ifndef GHOSTANIMATIONCOMPONENT_H
#define GHOSTANIMATIONCOMPONENT_H

#include "GEngine/Components/Component.h"

namespace GEngine
{
	class Sprite2dAnimatorComponent;
	class Sprite2dRendererComponent;
}

namespace PacMan
{
	struct GhostsStateData;

	class GhostAnimationComponent final : public GEngine::Component
	{
		REGISTER_COMPONENT(GhostAnimationComponent)

	public:
		explicit GhostAnimationComponent(
			GEngine::GEngineCoreModules* modules,
			const std::weak_ptr<GEngine::Entity> &entity,
			GhostsStateData* ghostsStateData,
			const std::weak_ptr<GEngine::Sprite2dRendererComponent> &spriteRendererComponent,
			const std::weak_ptr<GEngine::Sprite2dAnimatorComponent> &spriteAnimatorComponent
			);

		void OnTick() override;

	private:
		GhostsStateData* const _ghostsStateData;
		std::weak_ptr<GEngine::Sprite2dRendererComponent> _spriteRendererComponent;
		std::weak_ptr<GEngine::Sprite2dAnimatorComponent> _spriteAnimatorComponent;
	};
}

#endif //GHOSTANIMATIONCOMPONENT_H

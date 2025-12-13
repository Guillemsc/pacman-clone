//
// Created by guillem on 12/13/25.
//

#ifndef GHOSTANIMATIONCOMPONENT_H
#define GHOSTANIMATIONCOMPONENT_H

#include "GEngine/Components/Component.h"

namespace PacMan
{
	struct GhostsStateData;

	class GhostAnimationComponent final : public GEngine::Component
	{
	public:
		explicit GhostAnimationComponent(
			GEngine::GEngineCoreModules* modules,
			const std::weak_ptr<GEngine::Entity> &entity,
			GhostsStateData* ghostsStateData
			);

	private:
		GhostsStateData* const _ghostsStateData;
	};
}

#endif //GHOSTANIMATIONCOMPONENT_H

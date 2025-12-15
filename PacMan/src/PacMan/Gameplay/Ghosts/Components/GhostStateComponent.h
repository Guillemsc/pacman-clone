//
// Created by guillem on 12/15/25.
//

#ifndef GHOSTSTATECOMPONENT_H
#define GHOSTSTATECOMPONENT_H

#include "GEngine/Components/Component.h"

namespace PacMan
{
	class GhostStateComponent final : public GEngine::Component
	{
		REGISTER_COMPONENT(GhostStateComponent)

	public:
		using Component::Component;

	public:
		bool isReturningToPrision = false;
	};
}

#endif //GHOSTSTATECOMPONENT_H

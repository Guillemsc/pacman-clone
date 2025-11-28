//
// Created by guillem on 11/27/25.
//

#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H

#include "GEngine/Components/Component.h"

namespace PacMan
{
	class PlayerComponent final : public GEngine::Component
	{
		explicit PlayerComponent(GEngine::GEngineCoreModules* modules, const std::weak_ptr<GEngine::Entity> &entity);

		constexpr const char* GetTypeName() override { return "Player"; }
	};
}

#endif //PLAYERCOMPONENT_H

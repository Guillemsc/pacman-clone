//
// Created by guillem on 6/28/25.
//

#ifndef MAPMOVEMENTSYSTEM_H
#define MAPMOVEMENTSYSTEM_H

#include <memory>

#include "GEngine/Systems/System.h"

namespace GEngine
{
	class TiledMap2dRendererComponent;
}

namespace GEngine
{
	class Entity;
}

namespace Pacman
{
	class MapMovementSystem : public GEngine::System
	{
	public:
		MapMovementSystem(const std::weak_ptr<GEngine::Entity> &entity, const std::weak_ptr<GEngine::TiledMap2dRendererComponent> &tileComponent);

		void Tick() override;

	private:
		std::weak_ptr<GEngine::Entity> _entity;
		std::weak_ptr<GEngine::TiledMap2dRendererComponent> _tileComponent;
	};
}

#endif //MAPMOVEMENTSYSTEM_H

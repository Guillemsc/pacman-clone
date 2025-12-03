//
// Created by guillem on 12/3/25.
//

#ifndef ENTITYIDCOMPONENT_H
#define ENTITYIDCOMPONENT_H

#include "GEngine/Components/Component.h"
#include "PacMan/Gameplay/Entities/Enums/EntityType.h"

namespace PacMan
{
	class EntityIdComponent final : public GEngine::Component
	{
		DECLARE_COMPONENT(EntityIdComponent)

	public:
		explicit EntityIdComponent(GEngine::GEngineCoreModules *modules, const std::weak_ptr<GEngine::Entity> &entity);

		void SetType(EntityType type);
		EntityType GetType() const;

	private:
		EntityType _type = EntityType::UNDEFINED;
	};
}

#endif //ENTITYIDCOMPONENT_H

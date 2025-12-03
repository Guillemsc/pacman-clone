//
// Created by guillem on 11/28/25.
//

#ifndef REDGHOSTAICOMPONENT_H
#define REDGHOSTAICOMPONENT_H

#include "GhostAiComponent.h"

#include <memory>

namespace GEngine
{
	class Entity;
	class GEngineCoreModules;
}

namespace PacMan
{
	class RedGhostAiComponent final : public GhostAiComponent
	{
		DECLARE_COMPONENT(RedGhostAiComponent)

	public:
		explicit RedGhostAiComponent(GEngine::GEngineCoreModules *modules, const std::weak_ptr<GEngine::Entity> &entity);

		void OnDrawGuizmo() override;

	protected:
		glm::i32vec2 GetChaseTargetGridPosition() const override;
		glm::i32vec2 GetHideTargetGridPosition() const override;
	};
}

#endif //REDGHOSTAICOMPONENT_H

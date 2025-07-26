//
// Created by guillem on 7/26/25.
//

#ifndef METACONTEXT_H
#define METACONTEXT_H

#include <memory>

#include "Context.h"
#include "GEngine/Entities/Entity.h"

namespace PacMan
{
	class Coroutine;

	class MetaContext : public Context
	{
	public:
		std::shared_ptr<GEngine::Coroutine> OnLoad() override;
		void OnDispose() override;

	private:
		void WhenPlayButtonClicked();

	private:
		std::weak_ptr<GEngine::Entity> _rootUiEntity;
	};
}

#endif //METACONTEXT_H

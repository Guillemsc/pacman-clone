//
// Created by guillem on 6/7/25.
//

#ifndef TESTGAME_H
#define TESTGAME_H

#include "tokoro.h"
#include "GEngine/Coroutines/CoroutineRunner.h"
#include "GEngine/Games/Game.h"
#include "glm/fwd.hpp"
#include "glm/vec2.hpp"

namespace GEngine
{
	class TiledMap2dRendererComponent;
	class Entity;
}

namespace PacMan
{
	class ContextsStack;

	class PacManGame final : public GEngine::Game
	{
	public:
		void Init() override;
		void Tick(float deltaTime) override;
		void Dispose() override;

	private:
		tokoro::Async<void> LaunchGameAsync();

	private:
		std::unique_ptr<ContextsStack> _contextsStack;
	};
}



#endif //TESTGAME_H

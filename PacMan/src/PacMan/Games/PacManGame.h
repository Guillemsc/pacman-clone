//
// Created by guillem on 6/7/25.
//

#ifndef TESTGAME_H
#define TESTGAME_H

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
	class PacManGame : public GEngine::Game
	{
	public:
		~PacManGame() override;

		void Init() override;
		void Tick() override;
		void Dispose() override;
	};
}



#endif //TESTGAME_H

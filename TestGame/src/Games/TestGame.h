//
// Created by guillem on 6/7/25.
//

#ifndef TESTGAME_H
#define TESTGAME_H

#include "Games/Game.h"

namespace GEngineCore
{
	class Entity;
}

class TestGame : public GEngineCore::Game
{
public:
	~TestGame() override;

	void Init() override;
	void Tick() override;
	void Dispose() override;

private:
	std::weak_ptr<GEngineCore::Entity> _entity1;
};



#endif //TESTGAME_H

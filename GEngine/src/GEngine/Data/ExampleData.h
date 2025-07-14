//
// Created by guillem on 7/12/25.
//

#ifndef EXAMPLEDATA_H
#define EXAMPLEDATA_H

#include <memory>

#include "GEngine/Games/Game.h"

namespace GEngine
{
	struct ExampleData
	{
		std::string name;
		std::shared_ptr<Game> example;
	};
}

#endif //EXAMPLEDATA_H

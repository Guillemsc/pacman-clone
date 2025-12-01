//
// Created by guillem on 12/1/25.
//

#ifndef SPRITE2DANIMATION_H
#define SPRITE2DANIMATION_H

#include <string>
#include <vector>

namespace GEngine
{
	struct Sprite2dAnimation
	{
		std::string name = "";
		std::vector<int> animationFrames;
		float duration = 0.2f;
	};
}

#endif //SPRITE2DANIMATION_H

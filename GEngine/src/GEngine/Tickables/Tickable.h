//
// Created by guillem on 6/8/25.
//

#ifndef TICKABLE_H
#define TICKABLE_H

namespace GEngine
{
	class Tickable
	{
	public:
		virtual ~Tickable() = default;
		virtual void Tick() = 0;
	};
}

#endif //TICKABLE_H

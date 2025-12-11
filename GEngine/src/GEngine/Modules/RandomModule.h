//
// Created by guillem on 12/11/25.
//

#ifndef RANDOMMODULE_H
#define RANDOMMODULE_H

#include <random>

namespace GEngine
{
	class RandomModule
	{
	public:
		explicit RandomModule();

		static int Range(int minIncluded, int maxExcluded);

	private:
		static std::mt19937 _rng;
	};
}

#endif //RANDOMMODULE_H

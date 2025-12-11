//
// Created by guillem on 12/11/25.
//

#include "RandomModule.h"

namespace GEngine
{
	RandomModule::RandomModule()
	{
		_rng = std::mt19937(std::random_device{}());
	}

	int RandomModule::Range(const int minIncluded, const int maxExcluded)
	{
		std::uniform_int_distribution dist(minIncluded, maxExcluded - 1);
		return dist(_rng);
	}

	std::mt19937 RandomModule::_rng;
}

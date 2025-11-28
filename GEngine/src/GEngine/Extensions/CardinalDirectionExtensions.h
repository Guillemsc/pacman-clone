//
// Created by guillem on 6/29/25.
//

#ifndef CARDINALDIRECTIONEXTENSIONS_H
#define CARDINALDIRECTIONEXTENSIONS_H

#include "GEngine/Directions/CardinalDirection.h"
#include "glm/fwd.hpp"

namespace GEngine
{
	class CardinalDirectionExtensions
	{
	public:
		static glm::i32vec2 GetDirectionVector(const CardinalDirection cardinalDirection)
		{
			switch (cardinalDirection)
			{
				case CardinalDirection::UP:
				{
					return { 0, 1 };
				}

				case CardinalDirection::RIGHT:
				{
					return { 1, 0 };
				}

				case CardinalDirection::DOWN:
				{
					return { 0, -1 };
				}

				case CardinalDirection::LEFT:
				{
					return { -1, 0 };
				}
			}

			return { 0, 0 };
		}

		static CardinalDirection GetCardinalDirection(const glm::i32vec2& direction)
		{
			if (direction.x < 0)
			{
				return CardinalDirection::LEFT;
			}

			if (direction.x > 0)
			{
				return CardinalDirection::RIGHT;
			}

			if (direction.y < 0)
			{
				return CardinalDirection::DOWN;
			}

			if (direction.y > 0)
			{
				return CardinalDirection::UP;
			}

			return CardinalDirection::LEFT;
		}

		static bool AreInverseDirections(const CardinalDirection direction1, const CardinalDirection direction2)
		{
			switch (direction1)
			{
				case CardinalDirection::UP:
				{
					return direction2 == CardinalDirection::DOWN;
				}

				case CardinalDirection::RIGHT:
				{
					return direction2 == CardinalDirection::LEFT;
				}

				case CardinalDirection::DOWN:
				{
					return direction2 == CardinalDirection::UP;
				}

				case CardinalDirection::LEFT:
				{
					return direction2 == CardinalDirection::RIGHT;
				}
			}

			return false;
		}
	};
}

#endif //CARDINALDIRECTIONEXTENSIONS_H

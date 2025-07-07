//
// Created by guillem on 7/7/25.
//

#ifndef COLOREXTENSIONS_H
#define COLOREXTENSIONS_H
#include "raylib.h"
#include "GEngine/Colors/Color01.h"

namespace GEngine
{
	class Color01Extensions
	{
	public:
		static Color ToRaylibColor(const Color01& color)
		{
			return {
				static_cast<unsigned char>(color.r * 255.0f),
				static_cast<unsigned char>(color.g * 255.0f),
				static_cast<unsigned char>(color.b * 255.0f),
				static_cast<unsigned char>(color.a * 255.0f)
			};
		}
	};
}

#endif //COLOREXTENSIONS_H

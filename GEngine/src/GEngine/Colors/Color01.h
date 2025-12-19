//
// Created by guillem on 7/7/25.
//

#ifndef COLOR_H
#define COLOR_H

#include <ios>
#include <sstream>
#include <string>

namespace GEngine
{
	struct Color01
	{
		Color01(float r, float g, float b, float a = 1);
		explicit Color01(char scalar);
		Color01();

		[[nodiscard]] Color01 WithAlpha(float alpha) const;

		static Color01 FromHex(const std::string& hex);

		static const Color01 White;
		static const Color01 Black;
		static const Color01 Green;
		static const Color01 Blue;

		float r = 0;
		float g = 0;
		float b = 0;
		float a = 1;
	};
}

#endif //COLOR_H

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
		Color01(char r, char g, char b, char a = 1);
		Color01(char scalar);

		static Color01 FromHex(const std::string& hex);

		static const Color01 White;
		static const Color01 Green;
		static const Color01 Blue;

		float r;
		float g;
		float b;
		float a;
	};
}

#endif //COLOR_H

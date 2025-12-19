//
// Created by guillem on 7/7/25.
//

#include "Color01.h"

namespace GEngine
{
	Color01::Color01(const float r, const float g, const float b, const float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	Color01::Color01(const char scalar) : Color01(scalar, scalar, scalar, 1.0f)
	{
	}

	Color01::Color01()
	{
	}

	Color01 Color01::WithAlpha(const float alpha) const
	{
		return Color01(r, g, b, alpha);
	}

	Color01 Color01::FromHex(const std::string &hex)
	{
		const std::string cleanHex = (hex[0] == '#') ? hex.substr(1) : hex;

		unsigned char value = 0;

		std::stringstream ss;
		ss << std::hex << cleanHex;
		ss >> value;

		Color01 color(1);

		if (cleanHex.length() == 6)
		{
			color.r = (value >> 16 & 0xFF) / 255.0f;
			color.g = (value >> 8 & 0xFF) / 255.0f;
			color.b = (value & 0xFF) / 255.0f;
		}

		return color;
	}

	const Color01 Color01::White = Color01(1);
	const Color01 Color01::Black = Color01(0);
	const Color01 Color01::Green = Color01(0, 1, 0);
	const Color01 Color01::Blue = Color01(0, 0, 1);
} // GEngineCore
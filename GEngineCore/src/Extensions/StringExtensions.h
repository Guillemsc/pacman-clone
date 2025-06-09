//
// Created by guillem on 6/9/25.
//

#ifndef STRINGEXTENSIONS_H
#define STRINGEXTENSIONS_H

#include <algorithm>
#include <string>

namespace GEngineCore
{
	class StringExtensions
	{
	public:
		static std::string ToLower(const std::string& input)
		{
			std::string result = input;

			std::transform(
				result.begin(),
				result.end(),
				result.begin(),
				[](unsigned char c) { return std::tolower(c); }
				);

			return result;
		}
	};
}

#endif //STRINGEXTENSIONS_H

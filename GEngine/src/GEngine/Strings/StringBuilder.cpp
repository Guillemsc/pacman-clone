//
// Created by guillem on 12/14/25.
//

#include "StringBuilder.h"

#include <cstring>

namespace GEngine
{
	StringBuilder::StringBuilder(const int capacity)
	{
		_buffer.reserve(capacity);
	}

	void StringBuilder::Clear()
	{
		_buffer.clear();
	}

	void StringBuilder::Append(const std::string_view& str)
	{
		_buffer.insert(_buffer.end(), str.begin(), str.end());
	}

	void StringBuilder::Append(const char *str)
	{
		Append(std::string_view(str, std::strlen(str)));
	}

	std::string StringBuilder::ToString() const
	{
		return std::string(_buffer.begin(), _buffer.end());
	}

	const char* StringBuilder::c_str()
	{
		if (_buffer.empty() || _buffer.back() != '\0')
		{
			_buffer.push_back('\0');
		}

		return _buffer.data();
	}
}

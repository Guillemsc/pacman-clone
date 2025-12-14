//
// Created by guillem on 12/14/25.
//

#ifndef STRINGBUILDER_H
#define STRINGBUILDER_H

#include <string_view>
#include <string>
#include <vector>

namespace GEngine
{
	class StringBuilder
	{
	public:
		explicit StringBuilder(int capacity = 0);

		void Clear();
		void Append(const std::string_view& str);
		void Append(const char* str);
		template<typename... Args>
		void AppendFormat(const char* fmt, Args... args);

		std::string ToString() const;
		const char* c_str();

	private:
		std::vector<char> _buffer;
	};

	template<typename... Args>
	void StringBuilder::AppendFormat(const char* fmt, Args... args)
	{
		const int sizeNeeded = std::snprintf(nullptr, 0, fmt, args...);
		if (sizeNeeded <= 0) return;

		const std::size_t oldSize = _buffer.size();
		_buffer.resize(oldSize + sizeNeeded + 1);

		std::snprintf(_buffer.data() + oldSize, sizeNeeded + 1, fmt, args...);
	}
}

#endif //STRINGBUILDER_H

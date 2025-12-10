//
// Created by guillem on 12/10/25.
//

#ifndef RAYLIBLOGGER_H
#define RAYLIBLOGGER_H

#include <cstdarg>

namespace GEngine
{
	class RaylibLogger
	{
	public:
		static void Init();

	private:
		static void RaylibToEngineCallback(int msgType, const char* text, std::va_list args);
	};
}

#endif //RAYLIBLOGGER_H

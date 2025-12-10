//
// Created by guillem on 12/10/25.
//

#include "RaylibLogger.h"
#include "GEngine/Logging/GEngineLog.h"
#include "GEngine/Raylib/RaylibWrapper.h"

namespace GEngine
{
	void RaylibLogger::Init()
	{
		SetTraceLogCallback(RaylibToEngineCallback);
	}

	void RaylibLogger::RaylibToEngineCallback(const int msgType, const char *text, std::va_list args)
	{
		thread_local char buffer[4096];

		vsnprintf(buffer, sizeof(buffer), text, args);

		switch (msgType)
		{
			case 0: // LOG_ALL
			case 1: // LOG_TRACE
				GENGINE_INFO("[raylib] {}", buffer);
				break;
			case 2: // LOG_DEBUG
				GENGINE_INFO("[raylib] {}", buffer);
				break;
			case 3: // LOG_INFO
				GENGINE_INFO("[raylib] {}", buffer);
				break;
			case 4: // LOG_WARNING
				GENGINE_WARN("[raylib] {}", buffer);
				break;
			case 5: // LOG_ERROR
				GENGINE_ERROR("[raylib] {}", buffer);
				break;
			case 6: // LOG_FATAL
				GENGINE_ERROR("[raylib] {}", buffer);
				break;
			default:
				GENGINE_INFO("[raylib] {}", buffer);
				break;
		}
	}
} // GEngine
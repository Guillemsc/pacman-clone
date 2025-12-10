//
// Created by guillem on 12/10/25.
//

#include "GEngine/Logging/GEngineLog.h"

#include <spdlog/sinks/stdout_color_sinks.h>

#include "GEngine/Raylib/RaylibLogger.h"

namespace GEngine
{
	void GEngineLog::Init()
	{
		_coreLogger = spdlog::stdout_color_mt("ENGINE");
		_coreLogger->set_level(spdlog::level::trace);

		_gameLogger = spdlog::stdout_color_mt("APP");
		_gameLogger->set_level(spdlog::level::trace);

		_coreLogger->set_pattern("[%H:%M:%S] [%n] [%^%l%$] %v");
		_gameLogger->set_pattern("[%H:%M:%S] [%n] [%^%l%$] %v");

		RaylibLogger::Init();
	}

	std::shared_ptr<spdlog::logger> GEngineLog::_coreLogger;
	std::shared_ptr<spdlog::logger> GEngineLog::_gameLogger;
}

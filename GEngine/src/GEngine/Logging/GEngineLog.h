//
// Created by guillem on 12/10/25.
//

#ifndef GENGINELOG_H
#define GENGINELOG_H

#include <memory>

#include "spdlog/logger.h"

namespace GEngine
{
	class GEngineLog
	{
	public:
		static void Init();

		static spdlog::logger* GetCoreLogger() { return _coreLogger.get(); }
		static spdlog::logger* GetGameLogger() { return _gameLogger.get(); }

	private:
		static std::shared_ptr<spdlog::logger> _coreLogger;
		static std::shared_ptr<spdlog::logger> _gameLogger;
	};
}

#define GENGINE_INFO(...) GEngine::GEngineLog::GetCoreLogger()->info(__VA_ARGS__)
#define GENGINE_WARN(...) GEngine::GEngineLog::GetCoreLogger()->warn(__VA_ARGS__)
#define GENGINE_ERROR(...) GEngine::GEngineLog::GetCoreLogger()->error(__VA_ARGS__)

#define GGAME_INFO(...) GEngine::GEngineLog::GetGameLogger()->info(__VA_ARGS__)
#define GCLIENT_WARN(...) GEngine::GEngineLog::GetGameLogger()->warn(__VA_ARGS__)
#define GCLIENT_ERROR(...) GEngine::GEngineLog::GetGameLogger()->error(__VA_ARGS__)

#endif //GENGINELOG_H

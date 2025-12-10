//
// Created by guillem on 12/6/25.
//

#include "ConfigurationModule.h"

#include "GEngine/Logging/GEngineLog.h"

namespace GEngine
{
    void ConfigurationModule::LoadConfiguration()
    {
        _configuration = JsonData::LoadFromFile("init.gengine");

        if (!_configuration.HasData())
        {
            GENGINE_WARN("Engine configuration 'init.gengine' could not be found at the root folder.");
        }
        else
        {
            GENGINE_INFO("Engine configuration 'init.gengine' loaded.");
        }
    }

    const JsonData& ConfigurationModule::GetConfig()
    {
        return _configuration;
    }
}

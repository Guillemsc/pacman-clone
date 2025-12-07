//
// Created by guillem on 12/6/25.
//

#include "ConfigurationModule.h"

namespace GEngine
{
    void ConfigurationModule::LoadConfiguration()
    {
        _configuration = JsonData::LoadFromFile("init.gengine");
    }

    const JsonData& ConfigurationModule::GetConfig()
    {
        return _configuration;
    }
}

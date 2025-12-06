//
// Created by guillem on 12/6/25.
//

#include "ConfigurationModule.h"

namespace GEngine
{
    void ConfigurationModule::Init()
    {
        _configuration = JsonData::LoadFromFile("init.gengine");
    }

    const JsonData& ConfigurationModule::GetConfiguration()
    {
        return _configuration;
    }
}

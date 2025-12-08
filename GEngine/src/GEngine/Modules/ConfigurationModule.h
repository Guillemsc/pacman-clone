//
// Created by guillem on 12/6/25.
//

#ifndef CONFIGURATIONMODULE_H
#define CONFIGURATIONMODULE_H

#include "GEngine/Data/JsonData.h"

namespace GEngine
{
    // Loads and holds the engine configuration json.
    class ConfigurationModule
    {
    public:
        void LoadConfiguration();

        const JsonData& GetConfig();

    private:
        JsonData _configuration;
    };
}

#endif //CONFIGURATIONMODULE_H

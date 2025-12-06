//
// Created by guillem on 12/6/25.
//

#ifndef CONFIGURATIONMODULE_H
#define CONFIGURATIONMODULE_H

#include "GEngine/Data/JsonData.h"

namespace GEngine
{
    class ConfigurationModule
    {
    public:
        void Init();

        const JsonData& GetConfiguration();

    private:
        JsonData _configuration;
    };
}

#endif //CONFIGURATIONMODULE_H

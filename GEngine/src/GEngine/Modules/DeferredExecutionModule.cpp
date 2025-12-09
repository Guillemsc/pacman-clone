//
// Created by guillem on 12/9/25.
//

#include "DeferredExecutionModule.h"

namespace GEngine
{
    void DeferredExecutionModule::Tick()
    {
        for (int i = _queue.size() - 1; i >= 0; i--)
        {
            _queue[i]();
        }

        _queue.clear();
    }

    void DeferredExecutionModule::Dispose()
    {
        _queue.clear();
    }

    void DeferredExecutionModule::Push(const std::function<void()>& func)
    {
        _queue.push_back(func);
    }
}

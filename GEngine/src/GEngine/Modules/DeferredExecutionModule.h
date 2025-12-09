//
// Created by guillem on 12/9/25.
//

#ifndef DEFERREDEXECUTIONMODULE_H
#define DEFERREDEXECUTIONMODULE_H

#include <functional>

namespace GEngine
{
    class DeferredExecutionModule
    {
    public:
        void Tick();
        void Dispose();

        void Push(const std::function<void()>& func);

    private:
        std::vector<std::function<void()>> _queue;
    };
}

#endif //DEFERREDEXECUTIONMODULE_H

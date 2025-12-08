//
// Created by guillem on 6/14/25.
//

#ifndef INPUTMODULE_H
#define INPUTMODULE_H

#include <memory>

#include "GEngine/Raylib/RaylibWrapper.h"
#include "glm/vec2.hpp"

namespace GEngine
{
    class GEngineCoreModules;

    class InputModule
    {
    public:
        void Init(GEngineCoreModules* modules);

        static bool IsKeyPressed(KeyboardKey keyboardKey);
        static bool IsKeyDown(KeyboardKey keyboardKey);
        static bool IsKeyReleased(KeyboardKey keyboardKey);
        static bool IsMouseButtonPressed(MouseButton mouseButton);
        static bool IsMouseButtonDown(MouseButton mouseButton);
        static bool IsMouseButtonReleased(MouseButton mouseButton);
        glm::vec2 GetMousePosition() const;

    private:
        GEngineCoreModules* _modules = nullptr;
    };
}

#endif //INPUTMODULE_H

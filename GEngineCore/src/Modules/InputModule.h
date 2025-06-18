//
// Created by guillem on 6/14/25.
//

#ifndef INPUTMODULE_H
#define INPUTMODULE_H

#include "raylib.h"
#include "glm/vec2.hpp"

namespace GEngineCore
{
    class InputModule
    {
    public:
        static bool IsKeyPressed(KeyboardKey keyboardKey);
        static bool IsKeyDown(KeyboardKey keyboardKey);
        static bool IsKeyReleased(KeyboardKey keyboardKey);
        static bool IsMouseButtonPressed(MouseButton mouseButton);
        static bool IsMouseButtonDown(MouseButton mouseButton);
        static bool IsMouseButtonReleased(MouseButton mouseButton);
        static glm::vec2 GetMousePosition();
    };
}

#endif //INPUTMODULE_H

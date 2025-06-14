//
// Created by guillem on 6/14/25.
//

#ifndef INPUTMODULE_H
#define INPUTMODULE_H

#include "raylib.h"

namespace GEngineCore
{
    class InputModule
    {
    public:
        static bool IsKeyPressed(KeyboardKey keyboardKey);
        static bool IsKeyDown(KeyboardKey keyboardKey);
        static bool IsKeyReleased(KeyboardKey keyboardKey);
    };
}

#endif //INPUTMODULE_H

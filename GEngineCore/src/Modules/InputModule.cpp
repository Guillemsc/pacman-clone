//
// Created by guillem on 6/14/25.
//

#include "InputModule.h"

#include "raylib.h"

namespace GEngineCore
{
    bool InputModule::IsKeyPressed(KeyboardKey keyboardKey)
    {
        return ::IsKeyPressed(keyboardKey);
    }

    bool InputModule::IsKeyDown(KeyboardKey keyboardKey)
    {
        return ::IsKeyDown(keyboardKey);
    }

    bool InputModule::IsKeyReleased(KeyboardKey keyboardKey)
    {
        return ::IsKeyReleased(keyboardKey);
    }
} // GEngineCore
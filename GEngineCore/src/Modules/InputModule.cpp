//
// Created by guillem on 6/14/25.
//

#include "InputModule.h"

#include "raylib.h"

namespace GEngineCore
{
    bool InputModule::IsKeyPressed(const KeyboardKey keyboardKey)
    {
        return ::IsKeyPressed(keyboardKey);
    }

    bool InputModule::IsKeyDown(const KeyboardKey keyboardKey)
    {
        return ::IsKeyDown(keyboardKey);
    }

    bool InputModule::IsKeyReleased(const KeyboardKey keyboardKey)
    {
        return ::IsKeyReleased(keyboardKey);
    }

    bool InputModule::IsMouseButtonPressed(const MouseButton mouseButton)
    {
        return ::IsMouseButtonPressed(mouseButton);
    }

    bool InputModule::IsMouseButtonDown(const MouseButton mouseButton)
    {
        return ::IsMouseButtonDown(mouseButton);
    }

    bool InputModule::IsMouseButtonReleased(const MouseButton mouseButton)
    {
        return ::IsMouseButtonReleased(mouseButton);
    }

    glm::vec2 InputModule::GetMousePosition()
    {
        const Vector2 mousePos = ::GetMousePosition();
        return glm::vec2(mousePos.x, mousePos.y);
    }
} // GEngineCore
//
// Created by guillem on 6/14/25.
//

#include "InputModule.h"

#include "raylib.h"
#include "WindowModule.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Extensions/Vec2Extensions.h"

namespace GEngine
{
    void InputModule::Init(GEngineCoreModules* modules)
    {
        _modules = modules;
    }

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

    glm::vec2 InputModule::GetMousePosition() const
    {
        const glm::vec2 windowSize = _modules->window->GetWindowSize();

        Vector2 mousePos = ::GetMousePosition();
        mousePos.y = windowSize.y - mousePos.y;

        return glm::vec2(mousePos.x, mousePos.y);
    }
} // GEngineCore
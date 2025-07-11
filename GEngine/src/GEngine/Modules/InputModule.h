//
// Created by guillem on 6/14/25.
//

#ifndef INPUTMODULE_H
#define INPUTMODULE_H

#include <memory>

#include "raylib.h"
#include "glm/vec2.hpp"

namespace GEngine
{
    class GEngineCoreApplication;

    class InputModule
    {
    public:
        void Init(const std::weak_ptr<GEngineCoreApplication> &appPtr);

        static bool IsKeyPressed(KeyboardKey keyboardKey);
        static bool IsKeyDown(KeyboardKey keyboardKey);
        static bool IsKeyReleased(KeyboardKey keyboardKey);
        static bool IsMouseButtonPressed(MouseButton mouseButton);
        static bool IsMouseButtonDown(MouseButton mouseButton);
        static bool IsMouseButtonReleased(MouseButton mouseButton);
        glm::vec2 GetMousePosition() const;

    private:
        std::weak_ptr<GEngineCoreApplication> _appPtr;
    };
}

#endif //INPUTMODULE_H

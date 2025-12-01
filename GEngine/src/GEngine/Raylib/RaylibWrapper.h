//
// Created by guillem on 12/1/25.
//

#ifndef RAYLIBWRAPPER_H
#define RAYLIBWRAPPER_H

//#if defined(_WIN32) || defined(_WIN64)

//#endif

#include "raylib.h"
#include "raymath.h"

inline void Raylib_CloseWindow() { ::CloseWindow(); }
inline void Raylib_ShowCursor() { ::ShowCursor(); }
inline void Raylib_HideCursor() { ::HideCursor(); }
inline bool Raylib_IsCursorHidden() { return ::IsCursorHidden(); }

//#if defined(_WIN32) || defined(_WIN64)


#endif //RAYLIBWRAPPER_H

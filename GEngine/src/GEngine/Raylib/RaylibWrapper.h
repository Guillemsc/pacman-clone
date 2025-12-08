//
// Created by guillem on 12/1/25.
//

#ifndef RAYLIBWRAPPER_H
#define RAYLIBWRAPPER_H

#include "raylib.h"
#include "raymath.h"

inline void Raylib_CloseWindow() { ::rlCloseWindow(); }
inline void Raylib_ShowCursor() { ::rlShowCursor(); }
inline void Raylib_HideCursor() { ::rlHideCursor(); }
inline bool Raylib_IsCursorHidden() { return ::rlIsCursorHidden(); }


#endif //RAYLIBWRAPPER_H

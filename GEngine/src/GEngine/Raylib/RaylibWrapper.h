//
// Created by guillem on 12/1/25.
//

#ifndef RAYLIBWRAPPER_H
#define RAYLIBWRAPPER_H

#if defined(_WIN32) || defined(_WIN64)
#define CloseWindow RaylibCloseWindow
#define ShowCursor RaylibShowCursor
#define HideCursor RaylibHideCursor
#define IsCursorHidden RaylibIsCursorHidden
#endif

#include "raylib.h"

#if defined(_WIN32) || defined(_WIN64)
#undef CloseWindow
#undef ShowCursor
#undef HideCursor
#undef IsCursorHidden

inline void CloseWindow() { RaylibCloseWindow(); }
inline void ShowCursor() { RaylibShowCursor(); }
inline void HideCursor() { RaylibHideCursor(); }
inline bool IsCursorHidden() { return RaylibIsCursorHidden(); }
#endif

#endif //RAYLIBWRAPPER_H

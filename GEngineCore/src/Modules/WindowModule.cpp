//
// Created by guillem on 6/7/25.
//

#include "WindowModule.h"

#include "raylib.h"

namespace GEngineCore
{
	void WindowModule::Init()
	{
		const int screenWidth = 1200;
		const int screenHeight = 850;

		InitWindow(screenWidth, screenHeight, "raylib [shapes] example - basic shapes drawing");

		SetTargetFPS(60);
	}

	bool WindowModule::CanRun()
	{
		return !WindowShouldClose();
	}

	void WindowModule::Tick()
	{

	}

	void WindowModule::Dispose()
	{
		CloseWindow();
	}
} // GEngineCore
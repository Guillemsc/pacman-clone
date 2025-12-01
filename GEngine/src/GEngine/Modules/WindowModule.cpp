//
// Created by guillem on 6/7/25.
//

#include "WindowModule.h"

#include "EntitiesModule.h"
#include "GEngine/Raylib/RaylibWrapper.h"
#include "UiModule.h"
#include "GEngine/Core/GEngineCoreApplication.h"

namespace GEngine
{
	void WindowModule::Init(GEngineCoreModules* modules)
	{
		_modules = modules;

		const int screenWidth = 1200;
		const int screenHeight = 850;

		SetConfigFlags(FLAG_WINDOW_RESIZABLE);

		InitWindow(screenWidth, screenHeight, "raylib [shapes] example - basic shapes drawing");

		SetTargetFPS(60);
	}

	bool WindowModule::CanRun()
	{
		return !WindowShouldClose();
	}

	void WindowModule::Tick()
	{
		CheckWindowSizeChanged();
	}

	void WindowModule::Dispose()
	{
		Raylib_CloseWindow();
	}

	glm::i32vec2 WindowModule::GetWindowSize() const
	{
		int width = GetScreenWidth();
		int height = GetScreenHeight();

		return { width, height };
	}

	void WindowModule::CheckWindowSizeChanged()
	{
		const glm::i32vec2 currentWindowSize = GetWindowSize();
		const bool isDifferent = _previousWindowSize != currentWindowSize;
		_previousWindowSize = currentWindowSize;

		if (isDifferent)
		{
			OnWindowSizeChanged();
		}
	}

	void WindowModule::OnWindowSizeChanged() const
	{
		_modules->ui->RecalculateUiScaleAndRefreshUiTransforms();
	}
} // GEngineCore
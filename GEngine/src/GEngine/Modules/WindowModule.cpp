//
// Created by guillem on 6/7/25.
//

#include "WindowModule.h"

#include "EntitiesModule.h"
#include "raylib.h"
#include "GEngine/Core/GEngineCoreApplication.h"

namespace GEngine
{
	void WindowModule::Init(const std::weak_ptr<GEngineCoreApplication>& appPtr)
	{
		_appPtr = appPtr;

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
		CloseWindow();
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

	void WindowModule::OnWindowSizeChanged()
	{
		const std::shared_ptr<GEngineCoreApplication> app = _appPtr.lock();
		if (!app) return;

		const std::shared_ptr<EntitiesModule> entities = app->Entities().lock();

		if (entities)
		{
			entities->RefreshUiTransforms();
		}
	}
} // GEngineCore
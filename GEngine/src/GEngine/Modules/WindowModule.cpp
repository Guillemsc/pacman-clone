//
// Created by guillem on 6/7/25.
//

#include "WindowModule.h"

#include "ConfigurationModule.h"
#include "EntitiesModule.h"
#include "GEngine/Raylib/RaylibWrapper.h"
#include "UiModule.h"
#include "GEngine/Core/GEngineCoreApplication.h"

namespace GEngine
{
	void WindowModule::ApplyConfig(const JsonData& config)
	{
		const JsonData json = config.GetObject("Window");
		_titleInitialValue = json.GetString("Title");
		_sizeInitialValue = json.GetIVec2("Size", _sizeInitialValue);
		_fullscreenInitialValue = json.GetBool("Fullscreen", _fullscreenInitialValue);
		_resizableInitialValue = json.GetBool("Resizable", _resizableInitialValue);
		_vSyncInitialValue = json.GetBool("VSync", _vSyncInitialValue);
		_targetFramesInitialValue = json.GetInt("Target Frames", _targetFramesInitialValue);
	}

	void WindowModule::Init(GEngineCoreModules* modules)
	{
		_modules = modules;

		int configFlags = 0;

		if (_fullscreenInitialValue)
		{
			configFlags |= FLAG_FULLSCREEN_MODE;
		}

		if (_resizableInitialValue)
		{
			configFlags |= FLAG_WINDOW_RESIZABLE;
		}

		if (_vSyncInitialValue)
		{
			configFlags |= FLAG_VSYNC_HINT;
		}

		SetConfigFlags(configFlags);

		InitWindow(_sizeInitialValue.x, _sizeInitialValue.y, _titleInitialValue.c_str());

		SetTargetFPS(_targetFramesInitialValue);
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
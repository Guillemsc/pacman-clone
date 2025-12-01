//
// Created by guillem on 6/7/25.
//

#include "RenderingModule.h"

#include "CameraModule.h"
#include "GEngine/Raylib/RaylibWrapper.h"
#include "rlgl.h"
#include "GEngine/Cameras/Camera.h"
#include "GEngine/Cameras/Camera2d.h"

namespace GEngine
{
	RenderingModule::RenderingModule()
	{

	}

	void RenderingModule::Init(GEngineCoreModules* modules)
	{
		_modules = modules;

		_renderer2d = std::make_unique<Renderer2d>(modules);
		_uiRenderer = std::make_unique<UiRenderer>(modules);
		_guizmo2dRenderer = std::make_unique<Guizmo2dRenderer>(modules);
		_guizmoUiRenderer = std::make_unique<GuizmoUiRenderer>(modules);
		_imGuiRenderer = std::make_unique<ImGuiRenderer>();

		_imGuiRenderer->Init();
	}

	void RenderingModule::Tick()
	{
		RenderOnCurrentCamera();
	}

	void RenderingModule::Dispose()
	{
		_imGuiRenderer->Dispose();
	}

	void RenderingModule::RenderOnCurrentCamera() const
	{
		const bool isUsing2dMode = _modules->camera->IsUsing2dMode();

		BeginDrawing();

		constexpr Color clearColor = BLANK;
		ClearBackground(clearColor);

		if (isUsing2dMode)
		{
			const std::shared_ptr<Camera2d> currentCameraPtr = _modules->camera->GetCurrentRenderingCamera2d().lock();

			if (currentCameraPtr)
			{
				BeginMode2D(currentCameraPtr->GetRawCamera());

				_renderer2d->Render();
				_guizmo2dRenderer->Render();

				EndMode2D();
			}
		}
		else
		{
			const std::weak_ptr<Camera> currentCameraPtr = _modules->camera->GetCurrentRenderingCamera();
		}

		// Temp UI
		Camera2D uiCamera = { 0 };
		uiCamera.rotation = 0.0f;
		uiCamera.zoom = 1;

		BeginMode2D(uiCamera);
		_uiRenderer->Render();
		_guizmoUiRenderer->Render();
		EndMode2D();

		_imGuiRenderer->Render();

		EndDrawing();
	}
} // GEngineCore
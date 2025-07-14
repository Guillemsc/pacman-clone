//
// Created by guillem on 6/7/25.
//

#include "RenderingModule.h"

#include "CameraModule.h"
#include "raylib.h"
#include "rlgl.h"
#include "GEngine/Cameras/Camera.h"
#include "GEngine/Rendering/ImGuiRenderer.h"
#include "GEngine/Rendering/Renderer2d.h"
#include "GEngine/Rendering/UiRenderer.h"
#include "GEngine/Rendering/GuizmoUiRenderer.h"

namespace GEngine
{
	RenderingModule::RenderingModule()
	{

	}

	void RenderingModule::Init(const std::weak_ptr<GEngineCoreApplication> &appPtr)
	{
		_appPtr = appPtr;

		_renderer2d = std::make_shared<Renderer2d>();
		_uiRenderer = std::make_shared<UiRenderer>(appPtr);
		_guizmoUiRenderer = std::make_shared<GuizmoUiRenderer>(appPtr);
		_imGuiRenderer = std::make_shared<ImGuiRenderer>();

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
		const std::shared_ptr<GEngineCoreApplication> app = _appPtr.lock();
		if (!app) return;

		const std::shared_ptr<CameraModule> cameraModule = app->Camera().lock();
		if (!cameraModule) return;

		const std::weak_ptr<Camera> currentCameraPtr = cameraModule->GetCurrentRenderingCamera();

		Render(currentCameraPtr);
	}

	void RenderingModule::Render(const std::weak_ptr<Camera>& cameraPtr) const
	{
		const std::shared_ptr<Camera> camera = cameraPtr.lock();

		BeginDrawing();

		Color clearColor = BLANK;

		if (camera != nullptr)
		{

		}

		ClearBackground(clearColor);

		if (camera != nullptr)
		{
			BeginMode3D(camera->GetRawCamera());

			rlSetClipPlanes(0.01, 9999);

			_renderer2d->Render();
		}

		EndMode3D();

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
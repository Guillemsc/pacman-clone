//
// Created by guillem on 6/7/25.
//

#include "RenderingModule.h"

#include "CameraModule.h"
#include "raylib.h"
#include "Cameras/Camera.h"
#include "Rendering/ImGuiRenderer.h"

namespace GEngineCore
{
	RenderingModule::RenderingModule(const std::weak_ptr<CameraModule> &cameraModule)
	{
		_cameraModulePtr = cameraModule;

		_renderer2d = std::make_shared<Renderer2d>();
		_imGuiRenderer = std::make_shared<ImGuiRenderer>();
	}

	void RenderingModule::Init()
	{
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
		const std::shared_ptr<CameraModule> cameraModule = _cameraModulePtr.lock();
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

			_renderer2d->Render();

			EndMode3D();
		}

		_imGuiRenderer->Render();

		EndDrawing();
	}
} // GEngineCore
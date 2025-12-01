//
// Created by guillem on 6/7/25.
//

#ifndef RENDERINGMODULE_H
#define RENDERINGMODULE_H

#include <memory>

#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Rendering/Guizmo2dRenderer.h"
#include "GEngine/Rendering/GuizmoUiRenderer.h"
#include "GEngine/Rendering/ImGuiRenderer.h"
#include "GEngine/Rendering/Renderer2d.h"
#include "GEngine/Rendering/UiRenderer.h"

namespace GEngine
{
	class GEngineCoreApplication;
	class CameraModule;
	class Camera;
}

namespace GEngine
{
	class RenderingModule
	{
	public:
		explicit RenderingModule();

		void Init(GEngineCoreModules* modules);
		void Tick();
		void Dispose();

		Renderer2d* Render2d() const { return _renderer2d.get(); }
		UiRenderer* UiRender() const { return _uiRenderer.get(); }
		Guizmo2dRenderer* Guizmo2dRender() const { return _guizmo2dRenderer.get(); }
		GuizmoUiRenderer* GuizmoUiRender() const { return _guizmoUiRenderer.get(); }
		ImGuiRenderer* ImGuiRender() const { return _imGuiRenderer.get(); }

	private:
		void RenderOnCurrentCamera() const;

	private:
		GEngineCoreModules* _modules = nullptr;

		std::unique_ptr<Renderer2d> _renderer2d;
		std::unique_ptr<UiRenderer> _uiRenderer;
		std::unique_ptr<Guizmo2dRenderer> _guizmo2dRenderer;
		std::unique_ptr<GuizmoUiRenderer> _guizmoUiRenderer;
		std::unique_ptr<ImGuiRenderer> _imGuiRenderer;
	};
}

#endif //RENDERINGMODULE_H

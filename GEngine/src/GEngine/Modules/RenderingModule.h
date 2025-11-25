//
// Created by guillem on 6/7/25.
//

#ifndef RENDERINGMODULE_H
#define RENDERINGMODULE_H

#include <memory>

#include "GEngine/Core/GEngineCoreModules.h"

namespace GEngine
{
	class GEngineCoreApplication;
	class UiRenderer;
	class GuizmoUiRenderer;
	class Renderer2d;
	class ImGuiRenderer;
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

		std::weak_ptr<Renderer2d> Renderer2D() { return _renderer2d; }
		std::weak_ptr<UiRenderer> UiRender() { return _uiRenderer; }
		std::weak_ptr<GuizmoUiRenderer> GuizmoUiRender() { return _guizmoUiRenderer; }
		std::weak_ptr<ImGuiRenderer> ImGuiRender() { return _imGuiRenderer; }

	private:
		void RenderOnCurrentCamera() const;

	private:
		GEngineCoreModules* _modules = nullptr;

		std::shared_ptr<Renderer2d> _renderer2d;
		std::shared_ptr<UiRenderer> _uiRenderer;
		std::shared_ptr<GuizmoUiRenderer> _guizmoUiRenderer;
		std::shared_ptr<ImGuiRenderer> _imGuiRenderer;
	};
}

#endif //RENDERINGMODULE_H

//
// Created by guillem on 6/7/25.
//

#ifndef RENDERINGMODULE_H
#define RENDERINGMODULE_H

#include <memory>

namespace GEngine
{
	class GEngineCoreApplication;
	class UiRenderer;
	class Renderer2d;
	class CameraModule;
	class Camera;
}

namespace GEngine
{
	class ImGuiRenderer;
}

namespace GEngine
{
	class RenderingModule
	{
	public:
		explicit RenderingModule();

		void Init(const std::weak_ptr<GEngineCoreApplication> &appPtr);
		void Tick();
		void Dispose();

		std::weak_ptr<Renderer2d> Renderer2D() { return _renderer2d; }
		std::weak_ptr<UiRenderer> UiRender() { return _uiRenderer; }
		std::weak_ptr<ImGuiRenderer> ImGuiRender() { return _imGuiRenderer; }

	private:
		void RenderOnCurrentCamera() const;
		void Render(const std::weak_ptr<Camera>& cameraPtr) const;

	private:
		std::weak_ptr<GEngineCoreApplication> _appPtr;

		std::shared_ptr<Renderer2d> _renderer2d;
		std::shared_ptr<UiRenderer> _uiRenderer;
		std::shared_ptr<ImGuiRenderer> _imGuiRenderer;
	};
}

#endif //RENDERINGMODULE_H

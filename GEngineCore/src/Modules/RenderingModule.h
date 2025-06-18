//
// Created by guillem on 6/7/25.
//

#ifndef RENDERINGMODULE_H
#define RENDERINGMODULE_H

#include <memory>

#include "Rendering/Renderer2d.h"

namespace GEngineCore
{
	class CameraModule;
	class Camera;
}

namespace GEngineCore
{
	class ImGuiRenderer;
}

namespace GEngineCore
{
	class RenderingModule
	{
	public:
		RenderingModule(const std::weak_ptr<CameraModule>& cameraModule);

		void Init();
		void Tick();
		void Dispose();

		std::weak_ptr<Renderer2d> Render2D() { return _renderer2d; }
		std::weak_ptr<ImGuiRenderer> ImGuiRender() { return _imGuiRenderer; }

	private:
		void RenderOnCurrentCamera() const;
		void Render(const std::weak_ptr<Camera>& cameraPtr) const;

	private:
		std::weak_ptr<CameraModule> _cameraModulePtr;

		std::shared_ptr<Renderer2d> _renderer2d;
		std::shared_ptr<ImGuiRenderer> _imGuiRenderer;
	};
}

#endif //RENDERINGMODULE_H

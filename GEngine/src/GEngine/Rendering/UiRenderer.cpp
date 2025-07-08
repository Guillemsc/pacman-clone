//
// Created by guillem on 7/1/25.
//

#include "UiRenderer.h"

#include "GEngine/Extensions/Vec4Extensions.h"
#include "GEngine/Modules/WindowModule.h"

namespace GEngine
{
	UiRenderer::UiRenderer(const std::weak_ptr<GEngineCoreApplication> &appPtr)
	{
		_appPtr = appPtr;
	}

	void UiRenderer::Add(const std::int32_t layer, const std::function<void()> &func)
	{
		_renderQueue.Add(layer, func);
	}

	void UiRenderer::Render()
	{
		_renderQueue.Execute(true);
	}

	glm::vec2 UiRenderer::PositionToRenderPosition(const glm::vec2 &position) const
	{
		const std::shared_ptr<GEngineCoreApplication> app = _appPtr.lock();
		if (!app) return position;

		const std::shared_ptr<WindowModule> window = app->Window().lock();
		if (!window) return position;

		const glm::vec2 windowSize = window->GetWindowSize();

		const float newPositionY = windowSize.y - position.y;

		return { position.x, newPositionY };
	}

	glm::vec4 UiRenderer::RectToRenderRect(const glm::vec4 &rect) const
	{
		const std::shared_ptr<GEngineCoreApplication> app = _appPtr.lock();
		if (!app) return rect;

		const std::shared_ptr<WindowModule> window = app->Window().lock();
		if (!window) return rect;

		const glm::vec2 windowSize = window->GetWindowSize();
		const glm::vec2 rectSize = Vec4Extensions::GetSize(rect);

		glm::vec4 newRect = rect;

		newRect.y = windowSize.y - rect.y - rectSize.y;
		newRect.w = windowSize.y - rect.y;

		return newRect;
	}
} // GEngine
//
// Created by guillem on 7/11/25.
//

#include "GuizmoUiRenderer.h"

#include "raylib.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Data/CornersRect.h"
#include "GEngine/Extensions/Color01Extensions.h"
#include "GEngine/Modules/WindowModule.h"

namespace GEngine
{
	GuizmoUiRenderer::GuizmoUiRenderer(GEngineCoreModules* modules) : _modules(modules)
	{

	}

	void GuizmoUiRenderer::Add(const std::int32_t layer, const std::function<void()> &func)
	{
		_renderQueue.Add(layer, func);
	}

	void GuizmoUiRenderer::Render()
	{
		_renderQueue.Execute(true);
	}

	void GuizmoUiRenderer::AddCircle(const glm::vec2 &position, float radius, const Color01 &color)
	{
		Add(0, [this, position, radius, color]()
		{
			const glm::vec2 renderPosition = PositionToRenderPosition(position);
			const Color raylibColor = Color01Extensions::ToRaylibColor(color);
			DrawCircleLines(renderPosition.x, renderPosition.y, radius, raylibColor);
		});
	}

	void GuizmoUiRenderer::AddLineRect(const CornersRect& rect, const float thickness,const Color01 &color)
	{
		AddLine(rect.bottomLeft, rect.topLeft, thickness, color);
		AddLine(rect.topLeft, rect.topRight, thickness, color);
		AddLine(rect.topRight, rect.bottomRight, thickness, color);
		AddLine(rect.bottomRight, rect.bottomLeft, thickness, color);
	}

	void GuizmoUiRenderer::AddLine(const glm::vec2 &start, const glm::vec2 &end, float thickness, const Color01 &color)
	{
		Add(0, [this, color, start, end, thickness]()
		{
			const glm::vec2 renderStart = PositionToRenderPosition(start);
			const glm::vec2 renderEnd = PositionToRenderPosition(end);
			const Color raylibColor = Color01Extensions::ToRaylibColor(color);
			DrawLineEx({renderStart.x, renderStart.y}, {renderEnd.x, renderEnd.y}, thickness, raylibColor);
		});
	}

	glm::vec2 GuizmoUiRenderer::PositionToRenderPosition(const glm::vec2 &position) const
	{
		const glm::vec2 windowSize = _modules->window->GetWindowSize();

		const float newPositionY = windowSize.y - position.y;

		return { position.x, newPositionY };
	}
}

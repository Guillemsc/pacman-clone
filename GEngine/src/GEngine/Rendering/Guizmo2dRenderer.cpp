//
// Created by guillem on 12/1/25.
//

#include "Guizmo2dRenderer.h"

#include "GEngine/Extensions/Color01Extensions.h"
#include "GEngine/Data/CornersRect.h"
#include "glm/trigonometric.hpp"

namespace GEngine
{
	Guizmo2dRenderer::Guizmo2dRenderer(GEngineCoreModules *modules)
		: _modules(modules)
	{

	}

	void Guizmo2dRenderer::Add(const std::int32_t layer, const std::function<void()> &func)
	{
		_renderQueue.Add(layer, func);
	}

	void Guizmo2dRenderer::Render()
	{
		_renderQueue.Execute(true);
	}

	void Guizmo2dRenderer::AddCircle(const glm::vec2 &position, float radius, const Color01 &color)
	{
		Add(0, [this, position, radius, color]()
		{
			const glm::vec2 renderPosition = PositionToRenderPosition(position);
			const Color raylibColor = Color01Extensions::ToRaylibColor(color);
			DrawCircleLines(renderPosition.x, renderPosition.y, radius, raylibColor);
		});
	}

	void Guizmo2dRenderer::AddRect(const glm::vec2 &position, const glm::vec2 &size, float rotationRadians, const Color01 &color)
	{
		Add(0, [this, position, size, color, rotationRadians]()
		{
			const glm::vec2 renderPosition = PositionToRenderPosition(position);
			const float rotationDegrees = glm::degrees(rotationRadians);
			const Color raylibColor = Color01Extensions::ToRaylibColor(color);

			const Vector2 center = { size.x * 0.5f, size.y * 0.5f };

			const Rectangle rectangle = {
				renderPosition.x,
				renderPosition.y,
				size.x,
				size.y,
			};

			DrawRectanglePro(rectangle, center, rotationDegrees, raylibColor);
		});
	}

	void Guizmo2dRenderer::AddLine(const glm::vec2 &start, const glm::vec2 &end, float thickness, const Color01 &color)
	{
		Add(0, [this, color, start, end, thickness]()
		{
			const glm::vec2 renderStart = PositionToRenderPosition(start);
			const glm::vec2 renderEnd = PositionToRenderPosition(end);
			const Color raylibColor = Color01Extensions::ToRaylibColor(color);
			DrawLineEx({renderStart.x, renderStart.y}, {renderEnd.x, renderEnd.y}, thickness, raylibColor);
		});
	}

	glm::vec2 Guizmo2dRenderer::PositionToRenderPosition(const glm::vec2 &position) const
	{
		return { position.x, -position.y };
	}
}

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

	void GuizmoUiRenderer::Render()
	{
		for (auto it = _queue.begin(); it != _queue.end(); ++it)
		{
			const std::vector<GuizmoUiRendererCommand>& commands = it->second;

			for (auto commandIt = commands.begin(); commandIt != commands.end(); ++commandIt)
			{
				const GuizmoUiRendererCommand& command = *commandIt;
				RenderCommand(command);
			}

			it->second.clear();
		}
	}

	void GuizmoUiRenderer::AddLine(const glm::vec2 &start, const glm::vec2 &end, float thickness, const Color01 &color)
	{
		AddCommand(
			0,
			GuizmoUiRendererCommand {
				.type = GuizmoUiRendererCommandType::LINE,
				.line = {
					start,
					end,
					thickness,
					color
				}
			});
	}

	void GuizmoUiRenderer::AddCornersRectLines(const CornersRect& rect, const float thickness, const Color01 &color)
	{
		AddCommand(
			0,
			GuizmoUiRendererCommand {
				.type = GuizmoUiRendererCommandType::CORNERS_RECT_LINES,
				.cornersRectLines = {
					rect,
					thickness,
					color
				}
			});
	}

	void GuizmoUiRenderer::AddCircleLines(const glm::vec2 &position, const float radius, const Color01 &color)
	{
		AddCommand(
			0,
			GuizmoUiRendererCommand {
				.type = GuizmoUiRendererCommandType::CIRCLE_LINES,
				.circleLines = {
					position,
					radius,
					color
				}
			});
	}

	glm::vec2 GuizmoUiRenderer::PositionToRenderPosition(const glm::vec2 &position) const
	{
		const glm::vec2 windowSize = _modules->window->GetWindowSize();

		const float newPositionY = windowSize.y - position.y;

		return { position.x, newPositionY };
	}

	void GuizmoUiRenderer::AddCommand(const std::int32_t layer, const GuizmoUiRendererCommand &command)
	{
		_queue[layer].push_back(command);
	}

	void GuizmoUiRenderer::RenderCommand(const GuizmoUiRendererCommand &command) const
	{
		switch (command.type)
		{
			case GuizmoUiRendererCommandType::LINE:
			{
				RenderLineCommand(command.line);
				break;
			}

			case GuizmoUiRendererCommandType::CORNERS_RECT_LINES:
			{
				RenderRectLinesCommand(command.cornersRectLines);
				break;
			}

			case GuizmoUiRendererCommandType::CIRCLE_LINES:
			{
				RenderCircleLinesCommand(command.circleLines);
				break;
			}
		}
	}

	void GuizmoUiRenderer::RenderLineCommand(const LineGuizmoUiRendererCommand &command) const
	{
		const glm::vec2 renderStart = PositionToRenderPosition(command.start);
		const glm::vec2 renderEnd = PositionToRenderPosition(command.end);
		const Color raylibColor = Color01Extensions::ToRaylibColor(command.color);

		DrawLineEx({renderStart.x, renderStart.y}, {renderEnd.x, renderEnd.y}, command.thickness, raylibColor);
	}

	void GuizmoUiRenderer::RenderRectLinesCommand(const CornersRectLinesGuizmoUiRendererCommand &command) const
	{
		RenderLineCommand({ command.rect.bottomLeft, command.rect.topLeft, command.thickness, command.color });
		RenderLineCommand({ command.rect.topLeft, command.rect.topRight, command.thickness, command.color });
		RenderLineCommand({ command.rect.topRight, command.rect.bottomRight, command.thickness, command.color });
		RenderLineCommand({ command.rect.bottomRight, command.rect.bottomLeft, command.thickness, command.color });
	}

	void GuizmoUiRenderer::RenderCircleLinesCommand(const CircleLinesGuizmoUiRendererCommand &command) const
	{
		const glm::vec2 renderPosition = PositionToRenderPosition(command.position);
		const Color raylibColor = Color01Extensions::ToRaylibColor(command.color);

		DrawCircleLines(renderPosition.x, renderPosition.y, command.radius, raylibColor);
	}
}

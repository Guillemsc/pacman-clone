//
// Created by guillem on 12/1/25.
//

#include "GuizmoRenderer2d.h"

#include "GEngine/Extensions/Color01Extensions.h"
#include "GEngine/Data/CornersRect.h"
#include "GEngine/Extensions/MathExtensions.h"
#include "glm/trigonometric.hpp"

namespace GEngine
{
	GuizmoRenderer2d::GuizmoRenderer2d(GEngineCoreModules *modules)
		: _modules(modules)
	{

	}

	void GuizmoRenderer2d::Add(const std::int32_t layer, const std::function<void()> &func)
	{
		_renderQueue.Add(layer, func);
	}

	void GuizmoRenderer2d::Render()
	{
		for (auto it = _queue.begin(); it != _queue.end(); ++it)
		{
			const std::vector<GuizmoRenderer2dCommand>& commands = it->second;

			for (auto commandIt = commands.begin(); commandIt != commands.end(); ++commandIt)
			{
				const GuizmoRenderer2dCommand& command = *commandIt;
				RenderCommand(command);
			}

			it->second.clear();
		}
	}

	void GuizmoRenderer2d::AddCircle(const glm::vec2 &position, const float radius, const Color01 &color)
	{
		AddCommand(
			0,
			GuizmoRenderer2dCommand {
				.type = GuizmoRenderer2dCommandType::CIRCLE,
				.circle =  {
					position,
					radius,
					color
				}
			});
	}

	void GuizmoRenderer2d::AddRect(const glm::vec2 &position, const glm::vec2 &size, const float rotationRadians, const Color01 &color)
	{
		AddCommand(
			0,
			GuizmoRenderer2dCommand {
				.type = GuizmoRenderer2dCommandType::RECT,
				.rect =  {
					position,
					rotationRadians,
					size,
					color
				}
			});
	}

	void GuizmoRenderer2d::AddRectLines(
		const glm::vec2 &position,
		const glm::vec2 &size,
		const float rotationRadians,
		const float thickness,
		const Color01 &color
		)
	{
		AddCommand(
			0,
			GuizmoRenderer2dCommand {
				.type = GuizmoRenderer2dCommandType::RECT_LINES,
				.rectLines =  {
					position,
					rotationRadians,
					size,
					thickness,
					color
				}
			});
	}

	void GuizmoRenderer2d::AddLine(const glm::vec2 &start, const glm::vec2 &end, float thickness, const Color01 &color)
	{
		AddCommand(
		0,
			GuizmoRenderer2dCommand {
				.type = GuizmoRenderer2dCommandType::LINE,
				.line = {
					start,
					end,
					thickness,
					color
				}
			});
	}

	glm::vec2 GuizmoRenderer2d::PositionToRenderPosition(const glm::vec2 &position)
	{
		return { position.x, -position.y };
	}

	float GuizmoRenderer2d::RotationToRenderRotation(const float rotation)
	{
		return -rotation;
	}

	void GuizmoRenderer2d::AddCommand(const std::int32_t layer, const GuizmoRenderer2dCommand &command)
	{
		_queue[layer].push_back(command);
	}

	void GuizmoRenderer2d::RenderCommand(const GuizmoRenderer2dCommand &command)
	{
		switch (command.type)
		{
			case GuizmoRenderer2dCommandType::LINE:
			{
				RenderLineCommand(command.line);
				break;
			}

			case GuizmoRenderer2dCommandType::RECT:
			{
				RenderRectCommand(command.rect);
				break;
			}

			case GuizmoRenderer2dCommandType::RECT_LINES:
			{
				RenderRectLinesCommand(command.rectLines);
				break;
			}

			case GuizmoRenderer2dCommandType::CIRCLE:
			{
				RenderCircleCommand(command.circle);
				break;
			}
		}
	}

	void GuizmoRenderer2d::RenderLineCommand(const LineGuizmoRenderer2dCommand &command)
	{
		const glm::vec2 renderStart = PositionToRenderPosition(command.start);
		const glm::vec2 renderEnd = PositionToRenderPosition(command.end);
		const Color raylibColor = Color01Extensions::ToRaylibColor(command.color);

		DrawLineEx({renderStart.x, renderStart.y}, {renderEnd.x, renderEnd.y}, command.thickness, raylibColor);
	}

	void GuizmoRenderer2d::RenderRectCommand(const RectGuizmoRenderer2dCommand &command)
	{
		const glm::vec2 renderPosition = PositionToRenderPosition(command.position);
		const float rotationDegrees = RotationToRenderRotation(glm::degrees(command.rotationRadians));
		const Color raylibColor = Color01Extensions::ToRaylibColor(command.color);

		const Vector2 center = { command.size.x * 0.5f, command.size.y * 0.5f };

		const rlRectangle rectangle = {
			renderPosition.x,
			renderPosition.y,
			command.size.x,
			command.size.y,
		};

		DrawRectanglePro(rectangle, center, rotationDegrees, raylibColor);
	}

	void GuizmoRenderer2d::RenderRectLinesCommand(const RectLinesGuizmoRenderer2dCommand &command)
	{
		const glm::vec2 renderPosition = PositionToRenderPosition(command.position);
		const Color raylibColor = Color01Extensions::ToRaylibColor(command.color);

		const glm::vec2 halfSize = command.size * 0.5f;

		const float renderRotationRadians = RotationToRenderRotation(command.rotationRadians);
		const float cos = std::cos(renderRotationRadians);
		const float sin = std::sin(renderRotationRadians);

		const glm::vec2 localTopLeft = MathExtensions::RotatePointAroundOrigin({ -halfSize.x,  halfSize.y }, cos, sin);
		const glm::vec2 localBottomLeft = MathExtensions::RotatePointAroundOrigin({ -halfSize.x, -halfSize.y }, cos, sin);
		const glm::vec2 localBottomRight = MathExtensions::RotatePointAroundOrigin({  halfSize.x, -halfSize.y }, cos, sin);
		const glm::vec2 localTopRight = MathExtensions::RotatePointAroundOrigin({ halfSize.x,  halfSize.y }, cos, sin);

		const Vector2 topLeft = { renderPosition.x + localTopLeft.x, renderPosition.y + localTopLeft.y  };
		const Vector2 bottomLeft = { renderPosition.x + localBottomLeft.x, renderPosition.y + localBottomLeft.y  };
		const Vector2 bottomRight = { renderPosition.x + localBottomRight.x, renderPosition.y + localBottomRight.y  };
		const Vector2 topRight = { renderPosition.x + localTopRight.x, renderPosition.y + localTopRight.y  };

		DrawLineEx(topLeft, bottomLeft, command.thickness, raylibColor);
		DrawLineEx(bottomLeft, bottomRight, command.thickness, raylibColor);
		DrawLineEx(bottomRight, topRight, command.thickness, raylibColor);
		DrawLineEx(topRight, topLeft, command.thickness, raylibColor);
	}

	void GuizmoRenderer2d::RenderCircleCommand(const CircleGuizmoRenderer2dCommand &command)
	{
		const glm::vec2 renderPosition = PositionToRenderPosition(command.position);
		const Color raylibColor = Color01Extensions::ToRaylibColor(command.color);

		DrawCircleLines(renderPosition.x, renderPosition.y, command.radius, raylibColor);
	}
}

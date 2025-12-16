//
// Created by guillem on 7/1/25.
//

#include "UiRenderer.h"

#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Extensions/Color01Extensions.h"
#include "GEngine/Extensions/Vec4Extensions.h"
#include "GEngine/Modules/WindowModule.h"
#include "glm/detail/func_trigonometric.inl"

namespace GEngine
{
	UiRenderer::UiRenderer(GEngineCoreModules* modules)
		: _modules(modules)
	{

	}

	void UiRenderer::Render()
	{
		for (auto it = _queue.begin(); it != _queue.end(); ++it)
		{
			const std::vector<UiRendererCommand>& commands = it->second;

			for (auto commandIt = commands.begin(); commandIt != commands.end(); ++commandIt)
			{
				const UiRendererCommand& command = *commandIt;
				RenderCommand(command);
			}

			it->second.clear();
		}
	}

	void UiRenderer::AddRect(
		const std::int32_t layer,
		const glm::vec2 &position,
		const float rotationRadians,
		const glm::vec2 &size,
		const glm::vec2& center,
		const Color01 &color
		)
	{
		AddCommand(
			layer,
			UiRendererCommand {
				.type = UiRendererCommandType::RECT,
				.rect =  {
					position,
					rotationRadians,
					size,
					center,
					color
				}
			});
	}

	glm::vec2 UiRenderer::PositionToRenderPosition(const glm::vec2 &position) const
	{
		const glm::vec2 windowSize = _modules->window->GetWindowSize();

		const float newPositionY = windowSize.y - position.y;

		return { position.x, newPositionY };
	}

	glm::vec4 UiRenderer::RectToRenderRect(const glm::vec4 &rect) const
	{
		const glm::vec2 windowSize = _modules->window->GetWindowSize();
		const glm::vec2 rectSize = Vec4Extensions::GetSize(rect);

		glm::vec4 newRect = rect;

		newRect.y = windowSize.y - rect.y - rectSize.y;
		newRect.w = windowSize.y - rect.y;

		return newRect;
	}

	float UiRenderer::RotationToRenderRotation(const float rotation)
	{
		return -rotation;
	}

	void UiRenderer::AddCommand(const std::int32_t layer, const UiRendererCommand &command)
	{
		_queue[layer].push_back(command);
	}

	void UiRenderer::RenderCommand(const UiRendererCommand &command)
	{
		switch (command.type)
		{
			case UiRendererCommandType::RECT:
			{
				RenderRectCommand(command.rect);
				break;
			}
		}
	}

	void UiRenderer::RenderRectCommand(const RectUiRendererCommand &command)
	{
		const rlRectangle rect = { command.position.x, command.position.y, command.size.x, command.size.y};
		const float rotationDegrees = RotationToRenderRotation(glm::degrees(command.rotationRadians));
		const Color raylibColor = Color01Extensions::ToRaylibColor(command.color);

		DrawRectanglePro(rect, { command.center.x, command.center.y }, rotationDegrees, raylibColor);
	}
} // GEngine
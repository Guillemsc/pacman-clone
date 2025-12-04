//
// Created by guillem on 6/8/25.
//

#include "Renderer2d.h"

#include "GEngine/Raylib/RaylibWrapper.h"
#include "GEngine/Cameras/Camera.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Extensions/Color01Extensions.h"
#include "GEngine/Modules/WindowModule.h"

namespace GEngine
{
	Renderer2d::Renderer2d(GEngineCoreModules *modules)
		: _modules(modules)
	{
	}

	void Renderer2d::Add(const std::int32_t layer, const std::function<void()> &func)
	{
		_renderQueue.Add(layer, func);
	}

	void Renderer2d::Render()
	{
		Add(0, []()
		{
			DrawText("Hello, raylib!", 190, 200, 20, LIGHTGRAY);
		});

		Add(1, []()
		{
			DrawText("Hello, raylib! 2", 190, 200, 20, RED);
		});

		_renderQueue.Execute();
	}

	void Renderer2d::AddTexture(
		const std::int32_t layer,
		const Texture2D &texture,
		const Rectangle &source,
		const glm::vec2& position,
		const float rotationRadians,
		const glm::vec2& scale,
		const Color01& color
		)
	{
		Add(layer, [texture, source, scale, position, rotationRadians, color]()
		{
			const glm::vec2 size = { source.width * scale.x, source.height * scale.y };
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

			DrawTexturePro(texture, source, rectangle, center, rotationDegrees, raylibColor);
		});
	}

	void Renderer2d::AddRect(
		const std::int32_t layer,
		const glm::vec2 &position,
		float rotationRadians,
		const glm::vec2 &scale,
		const glm::vec2& size,
		const Color01 &color
		)
	{
		Add(layer, [this, position, size, color, rotationRadians, scale]()
		{
			const glm::vec2 renderPosition = PositionToRenderPosition(position);
			const float rotationDegrees = glm::degrees(rotationRadians);
			const glm::vec2 finalSize = { size.x * scale.x, size.y * scale.y };
			const Color raylibColor = Color01Extensions::ToRaylibColor(color);

			const Vector2 center = { size.x * 0.5f, size.y * 0.5f };

			const Rectangle rectangle = {
				renderPosition.x,
				renderPosition.y,
				finalSize.x,
				finalSize.y,
			};

			DrawRectanglePro(rectangle, center, rotationDegrees, raylibColor);
		});
	}

	void Renderer2d::DrawTexture(
		const Texture2D &texture,
		const Rectangle &source,
		const glm::vec2 &position,
		const float rotationRadians,
		const glm::vec2 &scale,
		const Color01 &color
		)
	{
		const glm::vec2 renderPosition = PositionToRenderPosition(position);
		const float rotationDegrees = glm::degrees(rotationRadians);
		const Vector2 size = { source.width * scale.x, source.height * scale.y };
		const Vector2 center = { size.x * 0.5f, size.y * 0.5f };
		const Rectangle dest = { renderPosition.x, renderPosition.y, size.x, size.y };
		const Color raylibColor = Color01Extensions::ToRaylibColor(color);

		DrawTexturePro(texture, source, dest, center, rotationDegrees, raylibColor);
	}

	glm::vec2 Renderer2d::PositionToRenderPosition(const glm::vec2 &position)
	{
		const glm::vec2 newPosition = { position.x, -position.y };
		return newPosition;
	}
} // GEngineCore
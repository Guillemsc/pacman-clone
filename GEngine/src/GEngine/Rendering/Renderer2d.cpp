//
// Created by guillem on 6/8/25.
//

#include "Renderer2d.h"

#include "GEngine/Raylib/RaylibWrapper.h"
#include "GEngine/Cameras/Camera.h"
#include "GEngine/Core/GEngineCoreModules.h"
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

	glm::vec2 Renderer2d::PositionToRenderPosition(const glm::vec2 &position) const
	{
		const glm::vec2 windowSize = _modules->window->GetWindowSize();
		const glm::vec2 halfWindowSize = windowSize * 0.5f;

		const glm::vec2 newPosition = {position.x, -position.y};

		return newPosition;
	}
} // GEngineCore
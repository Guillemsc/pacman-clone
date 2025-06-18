//
// Created by guillem on 6/8/25.
//

#include "Renderer2d.h"

#include "raylib.h"
#include "Cameras/Camera.h"

namespace GEngineCore
{
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
} // GEngineCore
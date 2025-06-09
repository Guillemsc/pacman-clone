//
// Created by guillem on 6/8/25.
//

#include "Renderer2d.h"

#include "raylib.h"

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

		float screenWidth = GetScreenWidth();
		float screenHeight = GetScreenHeight();
		Camera2D camera = { 0 };
		camera.target = (Vector2){ 0, 0 };                 // World space origin is at the center
		camera.offset = (Vector2){ screenWidth / 2, screenHeight / 2 }; // Move (0,0) to center of screen
		camera.rotation = 0.0f;
		camera.zoom = 0.9f;

		BeginMode2D(camera);

		ClearBackground(RAYWHITE);

		_renderQueue.Execute();

		EndMode2D();
	}
} // GEngineCore
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



		Camera3D camera3d = { 0 };
		camera3d.position = (Vector3){ 0.0f, 0.0f, -50.0f };
		camera3d.target = { 0.0f, 0.0f, 1 };
		camera3d.up = { 0.0f, 1.0f, 0.0f };
		camera3d.fovy = -185.0f;
		camera3d.projection = CAMERA_ORTHOGRAPHIC;

		BeginMode3D(camera3d);

		ClearBackground(RAYWHITE);

		_renderQueue.Execute();

		EndMode3D();
	}
} // GEngineCore
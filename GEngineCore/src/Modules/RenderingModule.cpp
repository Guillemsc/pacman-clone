//
// Created by guillem on 6/7/25.
//

#include "RenderingModule.h"

#include "raylib.h"
#include "Rendering/ImGuiRenderer.h"

namespace GEngineCore
{
	RenderingModule::RenderingModule()
	{
		_renderer2d = std::make_shared<Renderer2d>();
		_imGuiRenderer = std::make_shared<ImGuiRenderer>();
	}

	void RenderingModule::Init()
	{
		_imGuiRenderer->Init();
	}

	void RenderingModule::Tick()
	{
		Render();
	}

	void RenderingModule::Dispose()
	{
		_imGuiRenderer->Dispose();
	}

	void RenderingModule::Render()
	{
		BeginDrawing();

		_renderer2d->Render();
		_imGuiRenderer->Render();

		EndDrawing();
	}
} // GEngineCore
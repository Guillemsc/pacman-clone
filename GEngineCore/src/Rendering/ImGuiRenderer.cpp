//
// Created by guillem on 6/9/25.
//

#include "ImGuiRenderer.h"

#include "rlImGui.h"

namespace GEngineCore
{
	void ImGuiRenderer::Init()
	{
		rlImGuiSetup(true);
	}

	void ImGuiRenderer::Render()
	{
		rlImGuiBegin();

		_renderQueue.Execute();

		rlImGuiEnd();
	}

	void ImGuiRenderer::Dispose()
	{
		rlImGuiShutdown();
	}

	void ImGuiRenderer::Add(const std::function<void()> &func)
	{
		_renderQueue.Add(func);
	}
}

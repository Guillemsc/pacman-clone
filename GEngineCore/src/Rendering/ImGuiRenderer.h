//
// Created by guillem on 6/9/25.
//

#ifndef IMGUIRENDERER_H
#define IMGUIRENDERER_H

#include "SimpleRenderQueue.h"

namespace GEngineCore
{
	class ImGuiRenderer
	{
	public:
		void Init();
		void Render();
		void Dispose();

		void Add(const std::function<void()> &func);

	private:
		SimpleRenderQueue _renderQueue;
	};
}

#endif //IMGUIRENDERER_H

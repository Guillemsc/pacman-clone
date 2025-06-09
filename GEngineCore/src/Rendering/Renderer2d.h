//
// Created by guillem on 6/8/25.
//

#ifndef RENDERER2D_H
#define RENDERER2D_H

#include "LayeredRenderQueue.h"

namespace GEngineCore
{
	class Renderer2d
	{
	public:
		void Add(std::int32_t layer, const std::function<void()> &func);
		void Render();

	private:
		LayeredRenderQueue _renderQueue;
	};
}

#endif //RENDERER2D_H

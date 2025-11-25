//
// Created by guillem on 6/8/25.
//

#ifndef RENDERER2D_H
#define RENDERER2D_H

#include "LayeredRenderQueue.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	class GEngineCoreModules;
}

namespace GEngine
{
	class Renderer2d
	{
	public:
		explicit Renderer2d(GEngineCoreModules* modules);

		void Add(std::int32_t layer, const std::function<void()> &func);
		void Render();

		glm::vec2 PositionToRenderPosition(const glm::vec2& position) const;

	private:
		GEngineCoreModules* const _modules = nullptr;

		LayeredRenderQueue _renderQueue;
	};
}

#endif //RENDERER2D_H

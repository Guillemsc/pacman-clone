//
// Created by guillem on 6/8/25.
//

#ifndef RENDERER2D_H
#define RENDERER2D_H

#include "LayeredRenderQueue.h"
#include "GEngine/Raylib/RaylibWrapper.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	struct Color01;
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

		void AddTexture(
			std::int32_t layer,
			const Texture2D& texture,
			const Rectangle& source,
			const glm::vec2& position,
			float rotationRadians,
			const glm::vec2& scale,
			const Color01& color
			);

		void AddRect(
			std::int32_t layer,
			const glm::vec2& position,
			float rotationRadians,
			const glm::vec2& scale,
			const glm::vec2& size,
			const Color01& color
			);

		static glm::vec2 PositionToRenderPosition(const glm::vec2& position);

	private:
		GEngineCoreModules* const _modules = nullptr;

		LayeredRenderQueue _renderQueue;
	};
}

#endif //RENDERER2D_H
